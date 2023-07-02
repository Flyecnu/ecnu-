##  <div style="text-align:center; font-size:20px;">**华东师范大学计算机科学与技术学院实验报告**</div>

| **课程名称：数据挖掘 ** | **年级：**2020级         | **实践作业成绩：**          |
| :---------------------- | :----------------------- | :-------------------------- |
| **指导教师**：兰曼      | **组长**：汪鑫星         | **提交作业日期**：2023/6/11 |
| **小组编号**：06        | **组员**：张宏伟、沈宇轩 | **实验名称**：KDD           |

[TOC]

##  **1、 实验名称：Paper-Author Identifification in KDD**

**目标**：给定作者 ID 和论文 ID，判断该作者是否写了这篇论文。



##  **2、 基准系统**

### **2.1 运行环境与前置依赖描述**

#### **2.1.1 基本环境**

​		• Python 3

#### **2.1.2** **依赖**

​		• numpy

​		• sklearn

​		• pandas



### **2.2 目录、运行方法**

参考**KDD**竞赛基准系统（Benchmark）描述文件



### **2.3 特征向量**

#### **2.3.1 共同作者**

很多论文都有多个作者，根据 PaperAuthor 统计每一个作者的 Top 10（当然可以是 Top20 或者其他 Top K）的 coauthor，对于一个作者论文对，计算 ID 为 pid 的论文的作者有没有出现 ID 为 aid 的作者的 Top 10 coauthor 中，可以简单计算 Top 10 coauthor 出现的个数，还可以算一个得分，每个出现 pid 论文的 Top 10 coauthor 可以根据他们跟 aid作者的合作次数算一个分数，然后累加。

```python
# 1. 简单计算top 10 coauthor出现的个数
def coauthor_1(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author):
    authorId = AuthorIdPaperId.authorId
    paperId = AuthorIdPaperId.paperId

    # 从PaperAuthor中，根据paperId找coauthor。
    curr_coauthors = list(map(str, list(PaperAuthor[PaperAuthor["PaperId"] == int(paperId)]["AuthorId"].values)))
    #
    top_coauthors = list(dict_coauthor[authorId].keys())

    # 简单计算top 10 coauthor出现的个数
    nums = len(set(curr_coauthors) & set(top_coauthors))

    return util.get_feature_by_list([nums])


# 2. 还可以算一个得分，每个出现pid论文的top 10 coauthor可以根据他们跟aid作者的合作次数算一个分数，然后累加，
def coauthor_2(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author):
    authorId = AuthorIdPaperId.authorId
    paperId = AuthorIdPaperId.paperId

    # 从PaperAuthor中，根据paperId找coauthor。
    curr_coauthors = list(map(str, list(PaperAuthor[PaperAuthor["PaperId"] == int(paperId)]["AuthorId"].values)))

    # {"authorId": 100}
    top_coauthors = dict_coauthor[authorId]

    score = 0
    for curr_coauthor in curr_coauthors:
        if curr_coauthor in top_coauthors:
            score += top_coauthors[curr_coauthor]

    return util.get_feature_by_list([score])
```



#### **2.3.2 字符串距离**

**PaperAuthor** 里面是有噪音的，同一个 **(authorid,paperid)** 可能出现多次，我把同一个 (authorid,paperid) 对的多个 **name** 和多个 **affiliation** 合并起来。例如得到**aid,pid,name1##name2##name3,aff1##aff2##aff3，##** 为分隔符。由 PaperAuthor 里可以知道论文的 **name** 和 **affiliation**，另一个方面我们可以根据 (authorid,paperid)对中的 authorid 到 author 表里找到对应的 name 和 affiliation，假设当前的作者论文对是 (aid,pid)，从 PaperAuthor 里得到的 name 串和 affiliation 串分别为**name1##name2##name3,aff1##aff2##aff3**，根据 aid 从 Author 表找到的 name 和 affliction分别为 name-a、affliction-a，这样我们可以算字符串的距离。

**算法有 2 种：**

1. name-a 与 name1##name2##name3 的距离，同理 affliction-a 和 aff1##aff2##aff3的距离

2. name-a 分别与name1、name2、name3 的距离，然后取平均，affliction-a同理

**距离的度量有 3 种：**

1. 编辑距离（levenshtein distance）

2. 最长公共子序列（LCS）

3. 最长公共子串（LSS）

   

## **3、 实验内容**

### **3.1. 分类器**

####  **3.1.1基本概念和特点**

1. **Logistic Regression (逻辑回归)：**

   - 逻辑回归是一种经典的统计分类模型，常用于解决二分类问题。
   - 它使用逻辑函数（如sigmoid函数）将输入特征映射到一个概率值，表示属于某个类别的可能性。
   - 逻辑回归通过学习最优的权重参数，以最大化似然函数或最小化损失函数来进行模型训练和预测。

2. **Decision Tree (决策树)：**

   - 决策树是一种基于树状结构的分类模型，通过对输入特征进行一系列分割和判断来预测目标变量。
   - 它以树的形式表示决策规则，其中每个内部节点表示一个特征的分割点，每个叶节点表示一个类别或结果。
   - 决策树的构建过程通常使用信息增益、基尼指数等指标来选择最优的分割特征和分割点。

3. **Naive Bayes (朴素贝叶斯)：**

   - 朴素贝叶斯是一种基于贝叶斯定理的概率分类模型，常用于文本分类和垃圾邮件过滤等任务。
   - 它假设输入特征之间相互独立，并利用贝叶斯公式计算后验概率，从而进行分类。
   - 朴素贝叶斯分类器通过学习类别的先验概率和特征的条件概率来进行预测。

4. **SVM (支持向量机)：**

   - 支持向量机是一种通过构建超平面来进行分类的模型，常用于线性和非线性分类问题。
   - 它通过寻找能够最大化类别间间隔的超平面来进行分类，同时使用支持向量来支持决策边界的确定。
   - SVM可以通过核函数将输入特征映射到高维空间，从而处理非线性可分问题。

5. **KNN (k最近邻)：**

   - K最近邻是一种基于实例的分类模型，根据最近邻样本的类别进行投票或计算权重，从而进行分类。
   - 它根据输入样本与训练集中最近邻样本的距离来确定类别，其中k表示选择的最近邻样本的数量。
   - KNN算法简单直观，但对大规模数据集和高维特征空间可能存在计算开销。

6. **Random Forest (随机森林)：**

   - 随机森林是一种基于决策树的集成学习模型，通过构建多个决策树来进行分类或回归任务。

      - 它通过随机抽取特征和样本来构建决策树，并通过投票或平均预测结果来进行最终的分类决策。

      - 随机森林具有较好的鲁棒性和泛化能力，并且可以用于特征选择和异常检测等任务。


7. **AdaBoost (自适应增强)：**
   - AdaBoost是一种基于集成学习的分类模型，通过串行训练多个弱分类器来提高整体性能。
   - 它通过调整训练样本的权重，使前一个分类器分错的样本在下一个分类器中得到更多关注。
   - AdaBoost将多个弱分类器的预测结果进行加权组合，以得到最终的分类结果。

8. **Voting Classifier (投票分类器)：**
   - 投票分类器是一种基于集成学习的模型，它结合了多个独立分类器的预测结果，通过投票或加权投票来进行最终的分类决策。
   
   - 投票分类器可以包括不同类型的分类器，如逻辑回归、决策树、支持向量机等。
   
   - 通过集成多个分类器的预测结果，投票分类器可以提高分类的准确性和鲁棒性。
   
     

### **3.2. 新增特征**

#### **3.2.1姓名缩写一致性**

我们发现有些作者的名字在不同的论文中采取了不同的表达方式（在 Author.csv 中多为全名，而 PaperAuthor.csv 中多为缩写）。例如 Carl E. Landwehr 这个人，可能会出现 C. E. Landwehr 或者 Carl Landwehr 等不同的表达方式，虽然他们表示的都是同一个人，但是在计算字符串距离的时候就会出现较大的差距。

故而我们对名字缩写后及逆行字符串相似度比较。出于方便的考虑，判断是否取所有单词首字母后能完全匹配。特征为缩写是否匹配。

```python
def nameConsistence(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, Paper):
    authorId = int(AuthorIdPaperId.authorId)
    paperId = int(AuthorIdPaperId.paperId)
    def f(s):
        ss = ''
        for w in s.split():
            ss += w[0]
        return ss
    

    a = Author[Author['Id'] == authorId].iloc[0]
    
    p_a = PaperAuthor[(PaperAuthor['PaperId'] == paperId) &
                     (PaperAuthor['AuthorId'] == authorId)]
    feature = list()

    for _, row in p_a.iterrows():
        if f(row.Name) == f(a.Name):
            feature.append(1)
            break
    else:
        feature.append(0)
    return util.get_feature_by_list(feature)
```



#### **3.2.2关键词和标题相关**

作者的所有论文的关键词和标题应该具有一致性。由于一个作者的擅长领域通常是固定的，所以如果突然出现了他的论文属于一个全新的领域， 那么极大概率这篇文章不是他写的。

把标题和关键词一起考虑并分词除去停用词，特征为该作者历史论文的平均关键词数量，以及该论文和其他论文的公共关键词数量。

设作者历史论文数组为`papers`，该论文为`paper`

则平均关键词数量为$(\sum_{p = papers.start}^{papers.end}p.keywords.len) /papers.len $

公共关键词数量为$len(set(paper) \cap set(\bigcup_{p=papers.start}^{papers.end}p.keywords))$

```python
def keyWords(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, Paper):
    def get_words(paper):
        s = str(paper.Title)
        if not pd.isna(paper.Keyword):
            s += paper.Keyword
        # print(s)
        words = re.split(r'[|\s;,]', s)
        words = [w for w in words if w and w not in nltk.corpus.stopwords.words('english') and not w.isdigit()]
        return words

    authorId = int(AuthorIdPaperId.authorId)
    paperId = int(AuthorIdPaperId.paperId)   
    p_a: pd.DataFrame = PaperAuthor[PaperAuthor['AuthorId'] == authorId]
    # print(paper_data[paper_data['Id'] == paper_id].iloc[0])
    kws = get_words(Paper[Paper['Id'] == paperId].iloc[0])

    feature = [len(kws)]
    if p_a.shape[0] == 0:
        feature += [0, 0]
    else:
        cnt = 0
        s = set()
        for _, row in p_a.iterrows():
            paper = Paper[Paper['Id'] == row.PaperId]
            if paper.shape[0] == 0:
                continue
            paper = paper.iloc[0]
            _kws = get_words(paper)
            cnt += len(_kws)
            if paper.Id != paperId:
                s.update(_kws)
        feature.append(cnt / p_a.shape[0]) # 历史论文的平均关键词数量
        feature.append(len(s.intersection(set(kws)))) # 该论文和其他论文的公共关键词数量

    return util.get_feature_by_list(feature)
```



#### **3.2.3 发表年份**

对于学者而言，发表的论文的时间应该具有一致性，即作者通常在特定的时间段内活跃，而在该时间段之外写的论文很可能是其他人撰写的。我们使用两个特征来表述这个一致性，分别为该论文发表时间与该作者 最早 和 最晚 发表论文的时间的差值。

在生成上述特征之前，确定提供的年份是否有效是一个需要解决的问题。在数据集中，一些论文的出版年份明显无效，如0、-1和800190。此外，对内部验证集的实验表明，排除1800年之前的出版年份可以提高整体性能。因此，我们将有效区间设置为公元1800年至2013年，并忽略区间之外的出版年份。针对缺失值，为了方便，我们不做处理，而是增加一个特征标记数据是否缺失。

设是否缺失为`invalid`，作者发表论文的所有时间为`years`，该论文发表时间为`p_year`

故而最终的特征为`invalid`、`p_year-min(years)`、`max(years)-p_year`

```python
def timeConsistence(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, Paper):
    authorId = int(AuthorIdPaperId.authorId)
    paperId = int(AuthorIdPaperId.paperId)
    p_a: pd.DataFrame = PaperAuthor[PaperAuthor['AuthorId'] == authorId]
    p_year = Paper[Paper['Id'] == paperId].iloc[0].Year

    feature = list()
    years = list()
    for _, row in p_a.iterrows():
        paper = Paper[Paper['Id'] == row.PaperId]
        if paper.shape[0] == 0:
            continue
        paper = paper.iloc[0]
        if 1800 <= paper.Year <= 2013:
            years.append(paper.Year)
    # print(p_year, years)
    if not years or not 1800 <= p_year <= 2013:
        feature += [0, 0, 0]
    else:
        feature += [1, p_year - min(years), max(years) - p_year]

    return util.get_feature_by_list(feature)
```



#### **3.2.4会议和期刊**

一个作者会有固定的会议、固定的期刊，如果出现了一个不相干的会议或者期刊，那么也就可以排除了。所以可以以作者在这篇论文的会议（或期刊）中发表过的次数作为一个特征。

因为特定的会议和期刊总是有个特地的针对领域，所以想尝试对会议和期刊划分为不同种类，再根据作者发表过的固定的会议、固定的期刊，来找到每个作家主要的研究领域。通过对会议和期刊进行聚类来实现划分。将单个会议或期刊用一个一维向量表示，该一维向量分表表示的每个编号的作者在这个会议或期刊上发表文章总数。

```python
# 打开预先生成的每个编号的作者在不同会议上发表文章次数 (筛选出次数 >=1)
def conference_cluster(AuthorConferenceCount_FILE):
	 AuthorConferenceCount = pandas.read_csv(AuthorConferenceCount_FILE)
	 row = list(AuthorConferenceCount['ConferenceId'])
 	 col = list(AuthorConferenceCount['AuthorId'])
   data = list(AuthorConferenceCount['AuthorConferenceCount'])
 	 X = sparse.coo_matrix((data, (row, col)))
	 y_pred = KMeans(n_clusters=100, random_state=9).fit_predict(X)
```



### **3**.**3.** **对已有特征改进**

#### **3.3.1字符串距离特征**

除了基准系统使用的三个字符串距离，我们另外引入了三个新的字符串距离，分别是 Jaro–Winkler 距离，雅卡尔指数，，以及对 token 排序后的 Levenshtein 距离（考虑到中西方姓名的排列顺序差异），并基于此对stringDistance1和stringDistance2做了一定程度的修改

```python
# 计算 a_name 与 name 的距离
feat_list.append(len(longest_common_subsequence(a_name, name)))
feat_list.append(len(longest_common_substring(a_name, name)))
feat_list.append(Levenshtein_distance(a_name, name))
feat_list.append(textdistance.JaroWinkler().__call__(a_name, name))
feat_list.append(textdistance.Jaccard().__call__(a_name, name))
feat_list.append(fuzz.token_sort_ratio(a_name, name))
```

另外我们修改了stringDistance2中取平均值的做法，改成取最小值，是为stringDistance_3

```python
lcs_distance = []
lss_distance = []
lev_distance = []
jar_distance = []
jac_distance = []
sor_distance = []
for _name in name.split("##"):
    lcs_distance.append(len(longest_common_subsequence(a_name, _name)))
    lss_distance.append(len(longest_common_substring(a_name, _name)))
    lev_distance.append(Levenshtein_distance(a_name, _name))
    jar_distance.append(textdistance.JaroWinkler().__call__(a_name, _name))
    # print(textdistance.JaroWinkler().__call__(a_name, _name))
    jac_distance.append(textdistance.Jaccard().__call__(a_name, _name))
    sor_distance.append(fuzz.token_sort_ratio(a_name, name))

feat_list += [np.min(lcs_distance), np.min(lss_distance), np.min(lev_distance),
              np.min(jar_distance), np.min(jac_distance), np.min(sor_distance)]
```



#### **3.3.2共作者信息**

在基准系统使用的两个信息基础上，我们另外引入了两个共作者信息，分别为 该作者的历史共同作者合作总次数 和 该论文的共同作者总数，

```python
def coauthor_3(AuthorIdPaperId, dict_coauthor, dict_paperIdAuthorId_to_name_aff, PaperAuthor, Author, Paper):
    authorId = int(AuthorIdPaperId.authorId)
    paperId = int(AuthorIdPaperId.paperId)
    
    p_a = PaperAuthor[(PaperAuthor['PaperId'] == paperId)]

    coauthors = dict_coauthor[str(authorId)]
    feature = [sum(coauthors.values()), p_a.shape[0]]
    # print(feature)
    return util.get_feature_by_list(feature)
```



### **3.4.验证特征有效性**

基于Random Forest，使用十折交叉验证的方法，测试单独使用某类特征的准确率： 

- 作者信息 （包含新增的姓名缩写一致性和改进的字符串距离）：0.9080252331836134 

- 发表年份 ：0.8236835355778501 

- 共同作者 ：0.8624795852389014

- 关键词和标题 ：0.9456690646489946

- 会议和期刊：0.9382342842

  <img src="/Users/zhanghongwei/Desktop/数据挖掘/73F0968E493648F2CC5152C62F854A84.png" alt="73F0968E493648F2CC5152C62F854A84" style="zoom:50%;" />

关键词和标题特征的准确率最高，说明关键词和标题对于确定论文的真实作者是非常有效的。而发表年份特征的准确率相对较低，说明仅仅依靠发表年份可能不足以准确地确定作者身份。

结果证明：前述特征对预测有效，可以使用



### **3.5.多个模型的结果合并**

采用了多个模型，不同的模型可能对不同的特征向量有优劣。所以可以采用多个模型进行训练，最后将结

果做一个汇总。可以采用集成学习方法，比如投票分类器（Voting Classifier。

```python
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier, VotingClassifier
from sklearn import svm

clf1 = RandomForestClassifier(n_estimators=100)
clf3 = AdaBoostClassifier()

self.clf = VotingClassifier(estimators=[('rf', clf1), ('ada', clf3)], voting='hard')

```



## **四、结果**

### **4.1分类器性能分析**

实验开始前未改进原特征和新增特征，尝试不同分类器，并依次记录每个分类器的准确率、召回率和F1分数：

<img src="数据挖掘/Accuracy3333333.png" alt="Accuracy3333333" style="zoom:6%;" />

<img src="/Users/zhanghongwei/Desktop/数据挖掘/F1——3333333.png" alt="F1——3333333" style="zoom:6%;" />

<img src="/Users/zhanghongwei/Desktop/数据挖掘/recall3333333.png" alt="recall3333333" style="zoom: 6%;" />

综上所述，Random Forest、AdaBoost和Voting Classifier 在精确度、召回率和F1分数上表现出色，而Decision Tree和SVM则相对较弱。优先使用Random Forest、AdaBoost和Voting Classifier分类器。

### **4.2最终结果**

在完成改进后，尝试各种分类器，AdaBoost效果最好，最高准确率稳定在 96% 左右。

<img src="/Users/zhanghongwei/Desktop/数据挖掘/Accuracy444673333333.png" alt="Accuracy444673333333" style="zoom:6%;" />

## **五、总结**

​	在这次KDD小组作业中，我们以基准系统中随即森林模型跑出来的准确率作为baseline。特征方面，在基准系统的基础上，对原有特征进行了一定的改进，但是体现在准确率上的提升几乎没有；继而，我们收集资料，了解前人在当时的竞赛下提出的新的特征，基于其论文进行了一定程度的复现，包括了姓名缩写一致性、关键词与标题一致性、发表年份一致性、会议与期刊一致性等四个特征。而模型方面，限于时间因素，也没有做出一些模型或者参数的改进，直接选取了基准系统中表现较好的AdaBoost进行预测。

​	或许预测结果仍然有缺憾，但在这个过程中，我们学习到了很多知识，并进一步加深了对课堂所学知识的理解。通过合作和协作，我们也完成了这个小组作业，并对机器学习和数据分析有了更深入的认识和实践经验。

​	学习、参考台湾国立大学团队在KDD Cup 2013第一赛道中的获胜解决方案：https://www.csie.ntu.edu.tw/~cjlin/papers/kddcup2013/kddcup2013track1.pdf