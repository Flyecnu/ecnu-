#!/usr/bin/env python
#encoding: utf-8
# import sys
# sys.setdefaultencoding('utf-8')
from authorIdPaperId import AuthorIdPaperId
import util


# 加载训练数据
def load_train_data(train_path):
    data = util.read_dict_from_csv(train_path)
    authorIdPaperIds = []
    for item in data:
        authorId = item["AuthorId"]

        # 构造训练正样本
        for paperId in item["ConfirmedPaperIds"].split(" "):
            authorIdPaperId = AuthorIdPaperId(authorId, paperId)
            authorIdPaperId.label = 1  # 正样本类标
            authorIdPaperIds.append(authorIdPaperId)

        # 构造训练负样本
        for paperId in item["DeletedPaperIds"].split(" "):
            authorIdPaperId = AuthorIdPaperId(authorId, paperId)
            authorIdPaperId.label = 0  # 负样本类标
            authorIdPaperIds.append(authorIdPaperId)

    return authorIdPaperIds


def load_test_data(test_path):
    data = util.read_dict_from_csv(test_path)
    authorIdPaperIds = []
    for item in data:
        authorId = item["AuthorId"]
        # 构造测试样本
        for paperId in item["PaperIds"].split(" "):
            authorIdPaperId = AuthorIdPaperId(authorId, paperId)
            authorIdPaperId.label = -1  # 待预测，暂时赋值为1...
            authorIdPaperIds.append(authorIdPaperId)

    return authorIdPaperIds

