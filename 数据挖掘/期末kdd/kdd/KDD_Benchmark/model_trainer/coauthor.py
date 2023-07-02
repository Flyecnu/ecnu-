#!/usr/bin/env python
#encoding: utf-8
import os
import sys
# reload(sys)
# sys.setdefaultencoding('utf-8')
sys.path.append("../")
import util
import json
from collections import Counter
import config


# 根据PaperAuthor.csv，获取每个作者的top k个共作者
def get_top_k_coauthors(paper_author_path, k, to_file):

    data = util.read_dict_from_csv(paper_author_path)

    dict_paperId_to_authors = {}
    for item in data:
        paperId = int(item["PaperId"])
        authorId = int(item["AuthorId"])
        if paperId not in dict_paperId_to_authors:
            dict_paperId_to_authors[paperId] = []
        dict_paperId_to_authors[paperId].append(authorId)

    dict_author_to_coauthor = {}
    for paperId in dict_paperId_to_authors:
        authors = dict_paperId_to_authors[paperId]
        n = len(authors)
        for i in range(n):
            for j in range(i+1, n):
                if authors[i] not in dict_author_to_coauthor:
                    dict_author_to_coauthor[authors[i]] = Counter()
                if authors[j] not in dict_author_to_coauthor:
                    dict_author_to_coauthor[authors[j]] = Counter()
                # coauthor
                dict_author_to_coauthor[authors[i]][authors[j]] += 1
                dict_author_to_coauthor[authors[j]][authors[i]] += 1

    print("取 top k...")
    # 取 top k
    # authorid --> { author1: 100, author2: 45}
    res = {}
    for authorId in dict_author_to_coauthor:
        res[authorId] = {}
        for coauthorId, freq in dict_author_to_coauthor[authorId].most_common(k):
            res[authorId][coauthorId] = freq

    print("dump...")
    json.dump(res, open(to_file, "w"), encoding="utf-8")


if __name__ == '__main__':
    k = 10
    get_top_k_coauthors(
        os.path.join(config.DATASET_PATH, "PaperAuthor.csv"),
        k,
        os.path.join(config.DATA_PATH, "coauthor.json"))

