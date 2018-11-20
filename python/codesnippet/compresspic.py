# encoding: utf-8

# 压缩图片
# https://www.zybuluo.com/liuhui0803/note/777980 Yelp是如何无损压缩图片的
from PIL import Image, ExifTags
import StringIO

import requests

imgurl = "http://cdnqy.aibaodata.com/pics/2018/11/12/A4CB3CE3-7701-4B8B-AA1C-55C04CB118A1.jpeg"

imgdata = requests.get(imgurl)
data = StringIO.StringIO(imgdata.content)  # 在内存中进行处理
img = Image.open(data)

# 控制图片的方向为正常方向
if hasattr(img, "_getexif"):
    exif = dict(
        (ExifTags.TAGS[k], v) for k, v in img._getexif().items()
        if k in ExifTags.TAGS)
    if exif.get('Orientation', 0) == 3:
        img=img.rotate(180, expand=True)
    elif exif.get('Orientation', 0) == 6:
        img=img.rotate(270, expand=True)
    elif exif.get('Orientation', 0) == 8:
        img=img.rotate(90, expand=True)

imgw, imgh = img.size
if imgw > 1024:  # 图片的尺寸太大, 则缩小一倍
    imgw = int(imgw/2)
    imgh = int(imgh/2)
img.thumbnail((imgw, imgh), resample=Image.ANTIALIAS)
img.save("savename", format="jpeg", quality=50)

# 获取图片的真实类型
import imghdr
imgpath = "xxx.jpg"
imgType = imghdr.what(imgpath)
