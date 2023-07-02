#encoding: utf-8
import sys
sys.path.append("../")
import json
import pandas
from model_trainer.evalution import get_prediction, Evalution
from model_trainer.data_loader import load_train_data
from model_trainer.data_loader import load_test_data
from model_trainer.make_feature_file import Make_feature_file
from feature_functions import *
from classifier import *


class Trainer(object):
    def __init__(self,
                classifier,
                model_path,
                feature_function_list,
                train_feature_path,
                test_feature_path,
                test_result_path):

        self.classifier = classifier
        self.model_path = model_path
        self.feature_function_list = feature_function_list
        self.train_feature_path = train_feature_path
        self.test_feature_path = test_feature_path
        self.test_result_path = test_result_path


    def make_feature_file(self, train_AuthorIdPaperIds, test_AuthorIdPaperIds, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author):

        print(("-"*120))
        print(("\n".join([f.__name__ for f in feature_function_list])))
        print(("-" * 120))

        print("make train feature file ...")
        Make_feature_file(train_AuthorIdPaperIds, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, self.feature_function_list, self.train_feature_path)
        print("make test feature file ...")
        Make_feature_file(test_AuthorIdPaperIds, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, self.feature_function_list, self.test_feature_path)


    def train_mode(self):
        self.classifier.train_model(self.train_feature_path, self.model_path)

    def test_model(self):
        self.classifier.test_model(self.test_feature_path, self.model_path, self.test_result_path)





if __name__ == "__main__":


    ''' 特征函数列表 '''
    feature_function_list = [
        coauthor_1,
        coauthor_2,
        # stringDistance_1,
        # stringDistance_2,
    ]

    ''' 分类器 '''
    # 决策树，NB，等
    # classifier = Classifier(skLearn_DecisionTree())
    classifier = Classifier(skLearn_NaiveBayes())
    # classifier = Classifier(skLearn_svm())
    # classifier = Classifier(skLearn_lr())
    # classifier = Classifier(skLearn_KNN())
    # classifier = Classifier(sklearn_RandomForestClassifier())
    # classifier = Classifier(skLearn_AdaBoostClassifier())
    # classifier = Classifier(sklearn_VotingClassifier())

    ''' model path '''
    model_path = config.MODEL_PATH

    ''' train feature_file & test feature_file & test result path '''
    train_feature_path = config.TRAIN_FEATURE_PATH
    test_feature_path = config.TEST_FEATURE_PATH
    test_result_path = config.TEST_RESULT_PATH

    ''' Trainer '''
    trainer = Trainer(classifier, model_path, feature_function_list, train_feature_path, test_feature_path, test_result_path)

    ''' load data '''
    print("loading data...")
    train_AuthorIdPaperIds = load_train_data(config.TRAIN_FILE)  # 加载训练数据
    test_AuthorIdPaperIds = load_test_data(config.TEST_FILE)  # 加载测试数据
    # coauthor, 共作者数据
    dict_coauthor = json.load(open(config.COAUTHOR_FILE), encoding="utf-8")
    # (paperId, AuthorId) --> {"name": "name1##name2", "affiliation": "aff1##aff2"}
    dict_paperIdAuthorId_to_name_aff \
        = json.load(open(config.PAPERIDAUTHORID_TO_NAME_AND_AFFILIATION_FILE), encoding="utf-8")
    # 使用pandas加载csv数据
    PaperAuthor = pandas.read_csv(config.PAPERAUTHOR_FILE)  # 加载 PaperAuthor.csv 数据
    Author = pandas.read_csv(config.AUTHOR_FILE) # 加载 Author.csv 数据
    print("data is loaded...")

    # 为训练和测试数据，抽取特征，分别生成特征文件
    trainer.make_feature_file(train_AuthorIdPaperIds, test_AuthorIdPaperIds, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author)
    # 根据训练特征文件，训练模型
    trainer.train_mode()
    # 使用训练好的模型，对测试集进行预测
    trainer.test_model()
    # 对模型的预测结果，重新进行整理，得到想要的格式的预测结果
    get_prediction(config.TEST_FEATURE_PATH, config.TEST_RESULT_PATH, config.TEST_PREDICT_PATH)

    ''' 评估,（预测 vs 标准答案）'''
    gold_file = config.GOLD_FILE
    pred_file = config.TEST_PREDICT_PATH
    cmd = "python evalution.py %s %s" % (gold_file, pred_file)
    os.system(cmd)







