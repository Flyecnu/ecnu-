#!/usr/bin/env python
#encoding: utf-8
# import sys
# reload(sys)
# sys.setdefaultencoding('utf-8')

# 将 (AuthorId, PaperId) 设计成类，表示我要 训练／预测 的样本
class AuthorIdPaperId(object):
    def __init__(self, authorId, paperId):
        self.authorId = authorId
        self.paperId = paperId
        self.label = None  # 类标
