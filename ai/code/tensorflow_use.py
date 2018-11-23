import tensorflow as tf

# 定义一个常量
hello = tf.constant('Hello, Tensorflow!')

# 建立一个session
sess = tf.Session()

# 通过session里面的run函数来运行结果
print(sess.run(hello))

# 关闭session
sess.close()

a = tf.constant(3)
b = tf.constant(4)
# 使用with方式使用session
with tf.Session() as sess:
    print("相加: %i" % sess.run(a+b))

# 注入机制, 将具体的实参注入到相应的placeholder中
a = tf.placeholder(tf.int16)
b = tf.placeholder(tf.int16)
add = tf.add(a, b)
mul = tf.multiply(a, b)

with tf.Session() as sess:
    # tf.placeholder为操作创建占位符, 然后使用feed_dict把具体的值放到占位符里.
    print("相加: {}".format(sess.run(add, feed_dict={a:3, b:4})))
    print("相乘: {}".format(sess.run(mul, feed_dict={a:3, b:4})))
    print("获取多个结果: {}".format(sess.run([mul, add], feed_dict={a:3, b:4})))

# 建立session的其他方法
# 交互式session, 一般在jupyter环境中使用
# sess = tf.InteractiveSession()

# 使用supervisor方式, 该方式会更加高级一些, 使用起来更加复杂, 可以自动管理session中的具体
# 任务, 如载入、载出检查点文件、写入tensorboard等, 另外该方法还支持分布式训练的部署

# 指定GPU运算
# 如果下载的是GPU版本, 运行过程中tensorflow能自动检测, 检测到GPU, tensorflow会尽可能的
# 利用找到的第一个GPU来执行操作
# 如果机器上有超过一个可用的GPU, 除第一个外其他的GPU默认是不参与计算的. 可以明确的将OP指派
# 给它们执行

# with tf.Session() as sess:
#     with tf.device("/gpu:1"):
#         a = tf.placeholder(tf.int16)

# 目前支持的设备包括以下几种:
# cpu:0  机器的cpu
# gpu:0  机器的第一个gpu
# gpu:1  机器的第二个gpu
'''
还可以通过tf.ConfigProto来构建一个config. 在config中指定相关的gpu, 并在session中传入
config='xx'来指定GPU操作.

tf.ConfigProto参数如下:
log_device_placement=True: 是否打印设备分配日志
allow_soft_placement=True: 如果指定的设备不存在, 允许TF自动分配设备

config = tf.ConfigProto(log_device_placement=True)
config.gpu_options.allow_growth = True  # 分配GPU的运算资源, 开始会分配少量的GPU容量
# 然后按需慢慢增加, 由于不会释放内存, 会导致碎片
sess = tf.Session(config=config)

gpu_options = tf.GPUOptions(allow_growth=True)
config = tf.ConfigProto(gpu_options=gpu_options)

# 分配固定大小的资源, 分配gpu的70%显存给tensorflow
gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.7)
'''
