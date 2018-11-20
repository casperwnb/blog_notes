# encoding: utf-8

# 具体的执行类型
class _Executable(object):
    def __init__(self, client, method, url):
        self.client = client
        self.method = method
        self.url = url

    def __call__(self, **kw):
        # kw用于记录传递过来的参数

        url = "{}/{}".format(self.client.baseurl, self.url)
        print("Executable url:{}, kw={}".format(url, kw))
        # 发送具体的HTTP请求
        # if self.methdo == 'GET':
        #     r = requests.get(url, kw)
        # else:
        #     r = requsts.post(url, data=kw)
        # return r.json()
        return {"code": 0, "msg": "success", "data": {}}

# 生成链式的请求url
class _Callable(object):
    def __init__(self, client, name):
        self.client = client
        self.name = name

    def __getattr__(self, attr):
        if attr == 'get':
            return _Executable(self.client, 'GET', self.name)
        elif attr == 'post':
            return _Executable(self.client, 'POST', self.name)
        else:
            name = "{}/{}".format(self.name, attr)
            return _Callable(self.client, name)

    def __call__(self, param):
        u = "{}/{}".format(self.name, param)
        return _Callable(self.client, u)

    def __str__(self):
        return self.name
    
    __repr__ = __str__

class APIClient(object):
    def __init__(self, baseurl="http://localhost:8080"):
        self.baseurl = baseurl

    def __getattr__(self, attr):
        if '__' in attr:
            return getattr(self, attr)
        else:
            attr = attr.lower()
            return _Callable(self, attr)


client = APIClient()

# 访问形如: http://domain/status/user/:username
# 具体的url为: http://domain/status/user/casper
data = client.status.user("casper").get(age=28)
print(data)

# 访问形如: http://domain/status/user
data = client.status.user.get()
print(data)
