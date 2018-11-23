# encoding: utf-8

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

plotdata = { "batchsize":[], "loss":[] }
def moving_average(a, w=10):
    if len(a) < w: 
        return a[:]    
    return [val if idx < w else sum(a[(idx-w):idx])/w for idx, val in enumerate(a)]


# 生成模拟数据
train_X = np.linspace(-1, 1, 100)
# y=2x, 加入噪声
train_Y = 2 * train_X + np.random.randn(*train_X.shape) * 0.3

#图形显示
plt.plot(train_X, train_Y, 'ro', label='Original data')
plt.legend()
plt.show()

tf.reset_default_graph()

# 1. 为每个角色添加IP地址和端口, 创建server
# 定义ip和端口
strps_hosts = "localhost:1681"
strworker_hosts = "localhost:1682,localhost:1683"

# 定义角色名称
strjob_name = "ps"
task_index = 0

ps_hosts = strps_hosts.split(',')
worker_hosts = strworker_hosts.split(',')
cluster_spec = tf.train.ClusterSpec(
    {'ps': ps_hosts,'worker': worker_hosts})

# 创建server
server = tf.train.Server(
    {'ps': ps_hosts,'worker': worker_hosts},
    job_name=strjob_name,
    task_index=task_index)

# 2. 为ps角色添加等待函数
# ps角色使用join进行等待
if strjob_name == 'ps':
  print("wait")
  server.join()  # ps角色使用server.join将线程挂起, 开始接受连接消息

# 3. 创建网络结构, 使用tf.device将全部的节点放在当前任务下
# tf.device函数中的任务是通过tf.train.replica_device_setter来指定,
# replica_device_setter中使用worker_device来定义具体任务名称, 使用
# cluster的配置来指定角色及对应的IP地址, 从而实现管理整个任务下的图节点.
with tf.device(
    tf.train.replica_device_setter(
        worker_device="/job:worker/task:%d" % task_index,
        cluster=cluster_spec)):
    X = tf.placeholder("float")
    Y = tf.placeholder("float")
    # 模型参数
    W = tf.Variable(tf.random_normal([1]), name="weight")
    b = tf.Variable(tf.zeros([1]), name="bias")

    # 为了使载入检查点文件时能够同步循环次数, 定义了global_step, 并将其放到优化
    # 器中, 每次运行一次优化器, global_step就会自动获得当期迭代的次数
    # 获得迭代次数
    global_step = tf.contrib.framework.get_or_create_global_step()
    
    # 前向结构
    z = tf.multiply(X, W)+ b
    tf.summary.histogram('z',z)  # 将预测值以直方图显示
    # 反向优化
    cost =tf.reduce_mean( tf.square(Y - z))
    tf.summary.scalar('loss_function', cost)  # 将损失以标量显示
    learning_rate = 0.01
    optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(
        cost,global_step=global_step)  # Gradient descent

    saver = tf.train.Saver(max_to_keep=1)
    merged_summary_op = tf.summary.merge_all()  # 合并所有summary

    # 将其前面的变量全部初始化, 因此一般要放大后面
    init = tf.global_variables_initializer()


#参数设置
training_epochs = 2200
display_step = 2

# 4. 创建supervisor, 管理session
sv = tf.train.Supervisor(
    # 表明是否为chief supervisor, 这里将task_index=0的worker设置为chief supervisors
    is_chief=(task_index == 0),

    # 检查点文件和summary文件保存的路径
    logdir="log/super/",

    # 使用初始化变量的函数
    init_op=init,
    summary_op=None,  # 自动保存summary文件, None不保存

    # 保存的对象, supervisor会自动保存检查点文件, 不想自动保存可设为None
    saver=saver,
    global_step=global_step,
    save_model_secs=5  # 保存检查点文件的时间间隔, 此处每5s保存一次
    )

# 连接目标角色创建session
# session中的内容, 直接迭代训练
# session中不再需要运行tf.global_varaialbes_initializer(),
# supervisor在建立时会调用传入的init_op进行初始化, 如果加了sess.run(
# tf.global_variables_initializer()) 会导致载入模型的变量被二次清空

with sv.managed_session(server.target) as sess:
    #sess.run(init)

    print("sess ok")
    print(global_step.eval(session=sess))
    
    for epoch in range(global_step.eval(session=sess),
        training_epochs*len(train_X)):
    
        for (x, y) in zip(train_X, train_Y):
            _, epoch = sess.run([optimizer,global_step],
                feed_dict={X: x, Y: y})
            # 生成summary
            summary_str = sess.run(merged_summary_op,feed_dict={X: x, Y: y})

            # 将summary 写入文件, 如果想手动保存检查点文件, 可以使用sv.saver.save
            # 设置自动保存检查点文件后, 手动保存任然有效
            # 在运行过程中终止, 再运行supervisor时会自动载入模型的参数, 不需要手动
            # 调用saver.restore
            sv.summary_computed(sess, summary_str, global_step=epoch)
            if epoch % display_step == 0:
                loss = sess.run(cost, feed_dict={X: train_X, Y:train_Y})
                print ("Epoch:", epoch+1, "cost=", loss,"W=", sess.run(W),
                    "b=", sess.run(b))
                if not (loss == "NA" ):
                    plotdata["batchsize"].append(epoch)
                    plotdata["loss"].append(loss)
                #sv.saver.save(sess,"log/mnist_with_summaries/",global_step=epoch)
          
    print (" Finished!")
    sv.saver.save(sess,"log/mnist_with_summaries/"+"sv.cpk",global_step=epoch)

sv.stop()
