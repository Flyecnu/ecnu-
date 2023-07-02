#coding:utf-8
import os, config
from sklearn.datasets import load_svmlight_file
from sklearn import svm, tree
from sklearn.ensemble import AdaBoostClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import VotingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier


class Strategy(object):
    def train_model(self, train_file_path, model_path):
        return None
    def test_model(self, test_file_path, model_path, result_file_path):
        return None

class Classifier(object):
    def __init__(self, strategy):
        self.strategy = strategy

    def train_model(self, train_file_path, model_path):
        self.strategy.train_model(train_file_path, model_path)

    def test_model(self, test_file_path, model_path, result_file_path):
        self.strategy.test_model(test_file_path, model_path, result_file_path)



''' skLearn '''

class skLearn_DecisionTree(Strategy):
    def __init__(self):
        self.trainer = "skLearn decisionTree"
        self.clf = tree.DecisionTreeClassifier()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))


class skLearn_NaiveBayes(Strategy):
    def __init__(self):
        self.trainer = "skLearn NaiveBayes"
        self.clf = GaussianNB()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        train_X = train_X.toarray()
        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        test_X = test_X.toarray()
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))

class skLearn_svm(Strategy):
    def __init__(self):
        self.trainer = "skLearn svm"
        self.clf = svm.LinearSVC()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))


class skLearn_lr(Strategy):
    def __init__(self):
        self.trainer = "skLearn LogisticRegression"
        self.clf = LogisticRegression()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))


class skLearn_KNN(Strategy):
    def __init__(self):
        self.trainer = "skLearn KNN"
        self.clf = KNeighborsClassifier(n_neighbors=3)
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))



class skLearn_AdaBoostClassifier(Strategy):
    def __init__(self):
        self.trainer = "skLearn AdaBoostClassifier"
        self.clf = AdaBoostClassifier()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))


class sklearn_RandomForestClassifier(Strategy):
    def __init__(self):
        self.trainer = "skLearn RandomForestClassifier"
        self.clf = RandomForestClassifier()
        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))


class sklearn_VotingClassifier(Strategy):
    def __init__(self):
        self.trainer = "skLearn VotingClassifier"

        clf1 = LogisticRegression()
        clf2 = svm.LinearSVC()
        clf3 = AdaBoostClassifier()

        self.clf = VotingClassifier(estimators=[('lr', clf1), ('svm', clf2), ('ada', clf3)], voting='hard')

        print("Using %s Classifier" % (self.trainer))

    def train_model(self, train_file_path, model_path):
        train_X, train_y = load_svmlight_file(train_file_path)

        print("==> Train the model ...")
        self.clf.fit(train_X, train_y)


    def test_model(self, test_file_path, model_path, result_file_path):

        print("==> Test the model ...")
        test_X, test_y = load_svmlight_file(test_file_path)
        pred_y = self.clf.predict(test_X)

        # write prediction to file
        with open(result_file_path, 'w') as fout:
            fout.write("\n".join(map(str, map(int, pred_y))))




if __name__ == "__main__":
    pass
