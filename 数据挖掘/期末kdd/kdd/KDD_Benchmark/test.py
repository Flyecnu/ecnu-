#!/usr/bin/env python
#encoding: utf-8
import json
import sys
# reload(sys)
# sys.setdefaultencoding('utf-8')
# from sklearn.externals.joblib import Memory
from sklearn.datasets import load_svmlight_file
from sklearn import svm

if __name__ == '__main__':

    train_X, train_y = load_svmlight_file("feature/train.feature")
    test_X, test_y = load_svmlight_file("feature/test.feature")

    clf = svm.SVC()
    clf.fit(train_X, train_y)

    print(clf.predict(test_X))


