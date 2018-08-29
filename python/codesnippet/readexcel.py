# encoding: utf-8
import xlrd  # pip install xlrd

def readExcel():
    """
    从excel中读取用户名和邮件地址
    """

    excelName = "xx.xlsx"
    excelHandle = xlrd.open_workbook(excelName)
    sheetOne = excelHandle.sheet_by_index(0)  # 表格索引从0开始

    nRows = sheetOne.nrows
    userData = []
    for rowIdx in xrange(1, nRows):
        # 通过索引获取每一行数据
        rowData = sheetOne.row_values(rowIdx)
        # 取第一行的第一列数据
        cName = rowData[0].encode("utf-8")
        eName = rowData[1].encode("utf-8")
        email = rowData[5].encode("utf-8")

        userData.append({"cName": cName, "eName": eName, "email": email})
    return userData
