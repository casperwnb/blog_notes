# encoding: utf-8
# 参考链接: https://mp.weixin.qq.com/s/yl0HYR9k1zAst4eH0p4wyA

def make_synchronized(func):
    import threading

    func.__lock__ = threading.Lock()
    def synced_func(*args, **kwargs):
        with func.__lock__:
            return func(*args, **kwargs)
    return synced_func

class Singleton(object):
    _instance = None

    @make_synchronized
    def __new__(cls, *args, **kwargs):
        if not isinstance(cls._instance, cls):
            cls._instance = object.__new__(cls, *args, **kwargs)
        return cls._instance

class Pool(Singleton):
    __first_init = False  #
    def __init__(self):
        if self.__class__.__first_init:
            return
        # self.pool = redis.ConnectionPool(host=host, port=port)
        self.pool = {"a": 10}
        self.__class__.__first_init = True

    def redis_instance(self):
        # redisPoolClient = redis.Redis(connection_pool=self.pool)
        # return redisPoolClient
        redisPool = self.pool
        print(id(redisPool))


def test1():
    r1 = Pool().redis_instance()
    r2 = Pool().redis_instance()

test1()
