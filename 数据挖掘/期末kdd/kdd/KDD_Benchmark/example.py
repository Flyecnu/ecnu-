# encoding: utf-8
# 将特征文件的每一行表示为一个类
class Example:
    def __init__(self, target, feature, comment=""):
        self.content = str(target) + " " + feature.feat_string
        self.comment = comment
