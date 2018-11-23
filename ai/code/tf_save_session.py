# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

plotdata = { "batchsize":[], "loss":[] }
def moving_average(a, w=10):
    if len(a) < w: 
        return a[:]    
    return [val if idx < w else sum(a[(idx-w):idx])/w for idx, val in enumerate(a)]

#生成模拟数据
train_X = np.linspace(-1, 1, 100)
# y=2x，但是加入了噪声
train_Y = 2 * train_X + np.random.randn(*train_X.shape) * 0.3

#显示模拟数据点
# plt.plot(train_X, train_Y, 'ro', label='Original data')
# plt.legend()
# plt.show()

tf.reset_default_graph()

# 创建模型
# 占位符
X = tf.placeholder("float")
Y = tf.placeholder("float")

# 模型参数
W = tf.Variable(tf.random_normal([1]), name="weight")
b = tf.Variable(tf.zeros([1]), name="bias")

# 前向结构
z = tf.multiply(X, W)+ b

#反向优化
cost =tf.reduce_mean(tf.square(Y - z))
learning_rate = 0.01
optimizer = tf.train.GradientDescentOptimizer(learning_rate).minimize(cost) #Gradient descent, 梯度下降算法

# 初始化变量
init = tf.global_variables_initializer()

# 训练参数
training_epochs = 20
display_step = 2

# 保存模型路径设置
savepath = "log/"
# saver = tf.train.Saver()

# 最多保存一个检查点文件, 新生成的模型会覆盖以前的模型
saver = tf.train.Saver(max_to_keep=1)

# 启动session
with tf.Session() as sess:
    sess.run(init)

    # Fit all training data
    for epoch in range(training_epochs):
        for (x, y) in zip(train_X, train_Y):
            sess.run(optimizer, feed_dict={X: x, Y: y})

        #显示训练中的详细信息
        if epoch % display_step == 0:
            loss = sess.run(cost, feed_dict={X: train_X, Y:train_Y})
            print ("Epoch:", epoch+1, "cost=", loss,"W=", sess.run(W), "b=", sess.run(b))
            if not (loss == "NA" ):
                plotdata["batchsize"].append(epoch)
                plotdata["loss"].append(loss)

    print (" Finished!")
    # 保存模型
    # saver.save(sess, savepath+"linermodel.cpkt")

    # 保存检查点
    saver.save(sess, savepath+"linermodel.cpkt", global_step=epoch)
    # 会在log目录下看到类似linermodel.cpkt-19*文件, 这就是检查点文件
    print ("cost=", sess.run(cost, feed_dict={X: train_X, Y: train_Y}), "W=", sess.run(W), "b=", sess.run(b))
    #print ("cost:",cost.eval({X: train_X, Y: train_Y}))

    #图形显示
    plt.plot(train_X, train_Y, 'ro', label='Original data')
    plt.plot(train_X, sess.run(W) * train_X + sess.run(b), label='Fitted line')
    plt.legend()
    plt.show()
    
    plotdata["avgloss"] = moving_average(plotdata["loss"])
    plt.figure(1)
    plt.subplot(211)
    plt.plot(plotdata["batchsize"], plotdata["avgloss"], 'b--')
    plt.xlabel('Minibatch number')
    plt.ylabel('Loss')
    plt.title('Minibatch run vs. Training loss')
     
    plt.show()

    print ("cal x=0.2, z=", sess.run(z, feed_dict={X: 0.2}))

# 重启一个session, 用于载入保存的模型
loader = tf.train.Saver()
with tf.Session() as s2:
    s2.run(tf.global_variables_initializer())
    loader.restore(s2, savepath+"linermodel.cpkt")
    print("load cal x=0.2, z={}".format(
        s2.run(z, feed_dict={X:0.2})
    ))

# 打印模型内容
from tensorflow.python.tools.inspect_checkpoint import print_tensors_in_checkpoint_file

# 打印出的结果中, tensor_name 后面跟的就是创建的变量名, 接着是它的数值.
print_tensors_in_checkpoint_file(savepath+"linermodel.cpkt", None, True)

# 重启一个session, 载入检查点
load_epoch = 19
with tf.Session() as s3:
    s3.run(tf.global_variables_initializer())
    saver.restore(s3, savepath+"linermodel.cpkt-"+str(load_epoch))
    print("checkpoint load x=0.2, y={}".format(
        s3.run(z, feed_dict={X:0.2})
    ))

'''
# 快速获取检查点文件:
ckpt = tf.train.get_checkpoint_state(ckpt_dir)
if ckpt and ckpt.model_checkpoint_path:
    saver.restore(sess, ckpt.model_checkpoint_path)

# 或者
kpt = tf.train.latest_checkpoint(savedir)
if kpt is not None:
    saver.restore(sess, kpt)
'''

'''
# 更简便地保存检查点
import tensorflow as tf
tf.reset_default_graph()

global_step = tf.train.get_or_create_global_step()
step = tf.assign_add(global_step, 1)

# 设置检查点路径为log/checkpoints, 默认时间间隔是10m, 必须定义global_step变量
with tf.train.MonitoredTrainingSession(checkpoint_dir="log/checkpoints", save_checkpoint_secs=2) as sess:
    print(sess.run([global_step]))
    while not sess.should_stop():  # 启用死循环, 当sess不结束时就不停止
        i = sess.run(step)
        print(i)
'''

