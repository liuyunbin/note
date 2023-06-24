
## 安装库
# install.packages("openxlsx")
# install.packages("ggplot2")
# install.packages("reshape2")
# install.packages("dplyr")

## 使用库
library(openxlsx)
library(ggplot2)
library(reshape2)
library(dplyr)

## 从文件获取数据
setwd("D:/文档-刘云宾")
df = read.xlsx("ECI排名.xlsx")

## 将 year 列转化为 日期格式
# df$year = as.Date(df$year,"%Y")

## 修改列名
df = rename(df,
 AH="安徽",
 BJ="北京",
 CQ="重庆",
 FJ="福建",
 GD="广东",
 GS="甘肃",
 GX="广西",
 GZ="贵州",
 HA="河南",
 HB="湖北",
 HE="河北",
 HI="海南",
 HL="黑龙江",
 HN="湖南",
 JL="吉林",
 JS="江苏",
 JX="江西",
 LN="辽宁",
 NM="内蒙古",
 NX="宁夏",
 QH="青海",
 SC="四川",
 SD="山东",
 SH="上海",
 SN="陕西",
 SX="山西",
 TJ="天津",
 XJ="新疆",
 XZ="西藏",
 YN="云南",
 ZJ="浙江")

## 重新组织数据
col_names = colnames(df) # 列名称

col_nums = ncol(df) # 列的个数
row_nums = nrow(df) # 行的个数, 即 年分数

### 处理 横标轴的刻度名称, 每 n 个 展示一个
n = 5
year_len = length(df[,1])
scale_x_names = vector(mode='character',length=year_len)
for (i in 1:year_len) {
	if (i %% n == 1) {
		scale_x_names[i] = year[i]
	}
}

### 处理 纵标轴的刻度名称, 每 n 个 展示一个
n = 10
scale_y_names = vector(mode='character', length=31)
for (i in 1:31) {
	if (i %% n == 1) {
		scale_y_names[i] = as.character(32 - i)
	}
}

df = melt(df, id = "year", variable.name = "city", value.name = "data")

#df$data = factor(as.character(df$data))

## 画图

# ggplot()     存入数据
ggplot(data = df,
       mapping = aes(x = year,
                     y = data,
                     group=city,
                     colour=city)) +
geom_line() +                           # 画线
geom_point(size=3, show.legend = TRUE)+                     # 画点
theme_bw() +                            # 去掉背景
theme(panel.grid=element_blank(),       # 去掉网格
	axis.ticks.x = element_blank(),   # 去掉 x 轴的刻度
      axis.ticks.y = element_blank(),   # 去掉 y 轴的刻度
      panel.border = element_blank()    # 去掉外边框
      ) +
scale_x_discrete(breaks=c(2000,         # 调整横坐标要展示的刻度标签
                          2005,
                          2010,
                          2015,
                          2020),
                 expand=c(0.01,0)
                 )+
scale_y_continuous( breaks=c(1,11,21,31), # 调整 纵坐标要展示的刻度标签
			  labels=c("1"="31",
                             "11"="21",
                             "21"="11",
                             "31"="1"),
			  expand=c(0.01,0),
			  sec.axis=dup_axis(
                        name = NULL,
  				breaks = c(1:31),
                        labels=c(1:31)
  		#		labels = waiver(),
  		#		guide = waiver()
			  )
			)+
guides(
	colour = guide_legend(
		title = NULL, # 去掉图例标题
		ncol = 1,      # 图例只要一列
		keyheight = 0.7
	)
) +
coord_fixed(ratio=3/5)+
labs(
    	x = "Year",           # x 轴
    	y = "Ranking(ECI)",   # y 轴
   	title = "标题")        # 标题

ggsave("1.pdf")
