# 关于Sklearn线性回归与手搓的代码的区别与Sklearn的优化

## 一：关于区别

![image-20250321221535911](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321221535956.png)

![image-20250321221618475](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321221618523.png)

我手动划分数据集，使用train_test_split函数来划分数据集

![image-20250321222348483](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321222348527.png)

![image-20250321222511366](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321222511421.png)

我手动标准化，Sklearn直接调用StandardScaler就迅速完成了。



![image-20250321222912863](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321222912909.png)

![image-20250321222939401](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321222939503.png)

我写的代码冗长，易出现错误，Sklearn直接使用fit进行模型训练，并且使用库函数计算MSE和R平方，简化代码并减少出错机会。

## 二：关于Sklearn的优化

使用库函数简化数据预处理、模型训练、预测和评估的过程，减少了手搓代码可能出现的错误。相比于我的手搓代码，它可以做到更简洁，更容易阅读，方便以后的维护与修改。

我看有资料说Sklearn中的矩阵计算是某种比较特殊的算法SVD，避免直接矩阵求逆

<img src="https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321223802626.png" alt="image-20250321223802504" style="zoom:67%;" />

![image-20250321223849188](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321223849228.png)

![image-20250321224102920](https://radiantheart.oss-cn-guangzhou.aliyuncs.com/myimage/20250321224103027.png)

相比于伪逆矩阵的话，这种方式处理获得的数值更好更稳定。

THE END OF WEEK 1 WORK

2025.03.21