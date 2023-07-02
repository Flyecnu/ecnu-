#!/usr/bin/env python
#encoding: utf-8
import os
import sys
import importlib
importlib.reload(sys)
# sys.setdefaultencoding('utf-8')
sys.path.append("../")
import util
import config
from confusion_matrix import Alphabet, ConfusionMatrix


# 对模型的预测结果，重新进行整理，得到想要的格式的预测结果
def get_prediction(test_feature_path, test_result_path, to_file):
    feature_list = [line.strip() for line in open(test_feature_path)]
    predict_list = [line.strip() for line in open(test_result_path)]

    dict_authorId_to_predict = {}
    for feature, predict in zip(feature_list, predict_list):
        paperId, authorId = feature.split(" # ")[-1].split(" ")
        paperId = int(paperId)
        authorId = int(authorId)

        if authorId not in dict_authorId_to_predict:
            dict_authorId_to_predict[authorId] = {}
            dict_authorId_to_predict[authorId]["ConfirmedPaperIds"] = []
            dict_authorId_to_predict[authorId]["DeletedPaperIds"] = []

        if predict == "1":
            dict_authorId_to_predict[authorId]["ConfirmedPaperIds"].append(paperId)
        if predict == "0":
            dict_authorId_to_predict[authorId]["DeletedPaperIds"].append(paperId)

    # to csv
    items = sorted(list(dict_authorId_to_predict.items()), key=lambda x: x[0])

    data = []
    for item in items:
        AuthorId = item[0]
        ConfirmedPaperIds = " ".join(map(str, item[1]["ConfirmedPaperIds"]))
        DeletedPaperIds = " ".join(map(str, item[1]["DeletedPaperIds"]))

        data.append({"AuthorId": AuthorId, "ConfirmedPaperIds": ConfirmedPaperIds, "DeletedPaperIds": DeletedPaperIds})

    util.write_dict_to_csv(["AuthorId", "ConfirmedPaperIds", "DeletedPaperIds"], data, to_file)


# 评估。（预测 vs 标准答案）
def Evalution(gold_file_path, pred_file_path):
    gold_authorIdPaperId_to_label = {}
    pred_authorIdPaperId_to_label = {}

    gold_data = util.read_dict_from_csv(gold_file_path)
    for item in gold_data:
        AuthorId = item["AuthorId"]
        # 正样本
        for paperId in item["ConfirmedPaperIds"].split(" "):
            gold_authorIdPaperId_to_label[(AuthorId, paperId)] = "1"
        # 负样本
        for paperId in item["DeletedPaperIds"].split(" "):
            gold_authorIdPaperId_to_label[(AuthorId, paperId)] = "0"

    pred_data = util.read_dict_from_csv(pred_file_path)
    for item in pred_data:
        AuthorId = item["AuthorId"]
        # 正样本
        for paperId in item["ConfirmedPaperIds"].split(" "):
            pred_authorIdPaperId_to_label[(AuthorId, paperId)] = "1"
        # 负样本
        for paperId in item["DeletedPaperIds"].split(" "):
            pred_authorIdPaperId_to_label[(AuthorId, paperId)] = "0"

    # evaluation
    alphabet = Alphabet()
    alphabet.add("0")
    alphabet.add("1")

    cm = ConfusionMatrix(alphabet)
    for AuthorId, paperId in gold_authorIdPaperId_to_label:
        gold = gold_authorIdPaperId_to_label[(AuthorId, paperId)]
        pred = pred_authorIdPaperId_to_label[(AuthorId, paperId)]
        cm.add(pred, gold)

    return cm



if __name__ == '__main__':
    gold_file_path = sys.argv[1]
    pred_file_path = sys.argv[2]

    cm = Evalution(gold_file_path, pred_file_path)
    # accuracy
    acc = cm.get_accuracy()
    # 打印评估结果
    print("")
    print("##" * 20)
    print("    评估结果, 以Accuracy为准")
    print("##" * 20)
    print("")
    cm.print_out()
