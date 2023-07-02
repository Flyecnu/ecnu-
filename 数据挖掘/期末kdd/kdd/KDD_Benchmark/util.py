#!/usr/bin/env python
#encoding: utf-8
import csv
import os
import sys

from feature import Feature
import importlib

importlib.reload(sys)
# sys.setdefaultencoding('utf-8')


# fieldnames = ['first_name', 'last_name']
# [{'first_name': 'Baked', 'last_name': 'Beans'}, {'first_name': 'Lovely', 'last_name': 'Spam'}]
def write_dict_to_csv(fieldnames, contents, to_file):
    with open(to_file, 'w') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(contents)


#[{'first_name': 'Baked', 'last_name': 'Beans'}, {'first_name': 'Lovely', 'last_name': 'Spam'}]
def read_dict_from_csv(in_file):
    if not os.path.exists(in_file):
        return []
    with open(in_file) as csvfile:
        return list(csv.DictReader(csvfile))



def get_feature_by_feat(dict, feat):
    feat_dict = {}
    if feat in dict:
        feat_dict[dict[feat]] = 1
    return Feature("", len(dict), feat_dict)

# [0, 1, 0, 1]
def get_feature_by_list(list):
    feat_dict = {}
    for index, item in enumerate(list):
        if item != 0:
            feat_dict[index+1] = item
    return Feature("", len(list), feat_dict)

def get_feature_by_feat_list(dict, feat_list):
    feat_dict = {}
    for feat in feat_list:
        if feat in dict:
            feat_dict[dict[feat]] = 1
    return Feature("", len(dict), feat_dict)


''' 合并 feature_list中的所有feature '''
def mergeFeatures(feature_list, name = ""):
    # print "-"*80
    # print "\n".join([feature_file.feat_string+feature_file.name for feature_file in feature_list])
    dimension = 0
    feat_string = ""
    for feature in feature_list:
        if dimension == 0:#第一个
            feat_string = feature.feat_string
        else:
            if feature.feat_string != "":
                #修改当前feature的index
                temp = ""
                for item in feature.feat_string.split(" "):
                    index, value = item.split(":")
                    temp += " %d:%s" % (int(index)+dimension, value)
                feat_string += temp
        dimension += feature.dimension

    merged_feature = Feature(name, dimension, {})
    merged_feature.feat_string = feat_string.strip()
    return merged_feature

def write_example_list_to_file(example_list, to_file):
    with open(to_file, "w") as fout:
        fout.write("\n".join([example.content + " # " + example.comment for example in example_list]))


def write_example_list_to_arff_file(example_list, dimension, to_file):
    with open(to_file, "w") as fout:
        out_lines = []

        out_lines.append("@relation kdd")
        out_lines.append("")
        for i in range(dimension):
            out_lines.append("@attribute attribution%d numeric" % (i+1))
        out_lines.append("@attribute class {0, 1}")

        out_lines.append("")
        out_lines.append("@data")

        for example in example_list:
            feature_list = [0.0] * dimension
            s = example.content.split(" ")
            target = s[0]
            for item in s[1:]:
                if item == "":
                    continue
                k, v = int(item.split(":")[0]) - 1, float(item.split(":")[1])
                feature_list[k] = v

            feature = ",".join(map(str, feature_list))

            out_lines.append("%s,%s" % (feature, target))

        fout.write("\n".join(out_lines))


if __name__ == '__main__':
    s  = "0 ".split(" ")
    print(s)