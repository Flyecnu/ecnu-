#encoding: utf-8
# import pyprind
import util
from example import Example


def Make_feature_file(authorIdPaperIds, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, feature_function_list, to_file):
    example_list = []
    dimension = 0

    # process_bar = pyprind.ProgPercent(len(authorIdPaperIds))
    for authorIdPaperId in authorIdPaperIds:
        # process_bar.update()

        features = [feature_function(authorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author) for feature_function in feature_function_list]
        #合并特征
        feature = util.mergeFeatures(features)
        dimension = feature.dimension
        #特征target
        target = authorIdPaperId.label
        if target is None:
            target = "-1"
        #example
        example = Example(target, feature)
        # example.comment = json.dumps({"paperId": authorIdPaperId.paperId, "authorId": authorIdPaperId.authorId})
        example.comment = "%s %s" % (authorIdPaperId.paperId, authorIdPaperId.authorId)

        example_list.append(example)

    util.write_example_list_to_file(example_list, to_file)
    # to arff file
    util.write_example_list_to_arff_file(example_list, dimension, to_file+".arff")



