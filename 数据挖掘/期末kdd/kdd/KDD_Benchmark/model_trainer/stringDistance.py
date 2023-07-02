#!/usr/bin/env python
#encoding: utf-8
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
sys.path.append("../")
import config
import json
import util

# 在paperauthor里面是又噪音的，同一个（authorid,paperid）可能出现多次，我做的是把同一个（authorid,paperid）对的多个name和多个affiliation合并起来。例如
# aid,pid,name1,aff1
# aid,pid,name2,aff2
# aid,pid,name3,aff3
# 得到aid,pid,name1##name2##name3,aff1##aff2##aff3,“##”为分隔符
def load_paperIdAuthorId_to_name_and_affiliation(PaperAuthor_PATH, to_file):

    d = {}
    data = util.read_dict_from_csv(PaperAuthor_PATH)
    for item in data:
        PaperId = item["PaperId"]
        AuthorId = item["AuthorId"]
        Name = item["Name"]
        Affiliation = item["Affiliation"]

        key = "%s|%s" % (PaperId, AuthorId)
        if key not in d:
            d[key] = {}
            d[key]["Name"] = []
            d[key]["Affiliation"] = []

        if Name != "":
            d[key]["Name"].append(Name)
        if Affiliation != "":
            d[key]["Affiliation"].append(Affiliation)

    t = {}
    for key in d:
        name = "##".join(d[key]["Name"])
        affiliation = "##".join(d[key]["Affiliation"])

        t[key] = {}
        t[key]["name"] = name
        t[key]["affiliation"] = affiliation

    json.dump(t, open(to_file, "w"), encoding="utf-8")

if __name__ == '__main__':
    load_paperIdAuthorId_to_name_and_affiliation(config.PAPERAUTHOR_FILE, config.DATASET_PATH + "/paperIdAuthorId_to_name_and_affiliation.json")


