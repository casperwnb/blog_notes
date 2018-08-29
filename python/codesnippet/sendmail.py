# encoding: utf-8

import types
import base64
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email import encoders
from email.utils import (COMMASPACE, formatdate)
from email.header import Header
from email.utils import (parseaddr, formataddr)

class MailMessage(object):
    '''邮件消息内容'''
    def __init__(self, subject, fromaddr, toaddr, content, cc=None):
        self.mailfrom = fromaddr
        self.mailto = toaddr

        self.msg = MIMEMultipart()
        self.msg['From'] = self.formatAddr(fromaddr)
        if type(subject) == types.UnicodeType:
            self.msg['Subject'] = '=?UTF-8?B?%s?=' % (base64.b64encode(subject.encode('utf-8')))
        else:
            self.msg['Subject'] = '=?UTF-8?B?%s?=' % (base64.b64encode(subject))

        if type(toaddr) in (types.TupleType, types.ListType):
            self.msg['To'] = COMMASPACE.join(toaddr)
        else:
            self.msg['To'] = toaddr

        if cc:
            if isinstance(cc, list):
                self.msg["Cc"] = COMMASPACE.join(cc)
            else:
                self.msg["Cc"] = cc
        
        self.msg['Date'] = formatdate(localtime=True)
        # 如果邮件内容乱码, 可以考虑添加如下信息
        # self.msg["Accept-Language"] = "zh-CN"
        # self.msg["Accept-Charset"] = "ISO-8859-1,utf-8"
        
        if content.find('<') >= 0 and content.find('>') > 0:
            self.msg.attach(MIMEText(content, 'html', 'utf-8'))
        else:
            self.msg.attach(MIMEText(content, 'plain', 'utf-8'))

    def append_file(self, filename, conttype):
        '''增加文件附件'''
        if isinstance(filename, types.UnicodeType):
            filename = filename.encode('utf-8')
            
            # 某些邮件系统会将中文的附件名识别为乱码
            encodefilename = '=?UTF-8?B?{}?='.format(base64.b64encode(filename))
        maintype, subtype = conttype.split('/')
        part = MIMEBase(maintype, subtype, charset='utf-8')
        part.set_payload(open(filename, 'rb').read())
        encoders.encode_base64(part)
        part.add_header('Content-Disposition', 'attachment', filename=encodefilename)
        self.msg.attach(part)

    def append_data(self, content, conttype='application/octet-stream', attachname=''):
        '''增加数据附件'''
        maintype, subtype = conttype.split('/')
        part = MIMEBase(maintype, subtype)
        part.set_payload(content)
        encoders.encode_base64(part)
        if attachname:
            part.add_header('Content-Disposition', 'attachment', filename=attachname)
        self.msg.attach(part)

    def formatAddr(self, fulladdr):
        """
        格式化发件人，收件人格式
        """
        name, addr = parseaddr(fulladdr)
        return formataddr((
            Header(name, "utf-8").encode(),
            addr.encode("utf-8") if isinstance(addr, unicode) else addr
        ))

    def tostring(self):
        return self.msg.as_string()

class MailSender(object):
    '''邮件发送'''
    def __init__(self, server, username, password):
        self.smtpserver = server
        self.username = username
        self.password = password

    def send(self, msg):
        '''实际发送邮件，msg为一个MailMessage对象'''
        try:
            conn = smtplib.SMTP(self.smtpserver)
            # conn.set_debuglevel(1)  # 可以打印调试信息
            conn.login(self.username, self.password)
            conn.sendmail(msg.mailfrom, msg.mailto, msg.tostring())
            conn.quit()
            print('mail to:{} send succeed!'.format(str(msg.mailto)))
            return True
        except Exception, e:
            print('mail to:{} send error! {}'.format(str(msg.mailto), str(e)))
            return False
        
def sendmail(mailfrom, mailto, subject, content, files=None):
    # subject, from, to, content, cc(抄送)
    # from可以写成类似: "python爱好者 <email_addr>"
    m = MailMessage(subject, mailfrom, mailto, content)

    if files:
        if type(files) in (types.TupleType, types.ListType):
            for f in files:
                m.append_file(f, 'application/octet-stream')
        elif type(files) in (types.StringType, types.UnicodeType):
            m.append_file(files, 'application/octet-stream')

    # smtp_server, user, pwd
    # 网易: smtp.163.com, smtp.188.com, smtp.126.com
    # 腾讯企业: smtp.exmail.qq.com
    # 腾讯邮箱: smtp.qq.com
    sender = MailSender('', '', '')
    return sender.send(m)

