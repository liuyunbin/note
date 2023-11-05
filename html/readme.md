
# HTML
## 超文本的标记语言
* 超文本: 指超链接
* 标记: 各种元素的类型
* 元素的默认效果不重要, 语义重要

## 整体分类
* 块级元素
    * 每个块级元素独占一行, 多个块级元素从上往下排列
    * 默认宽度: 占满这个父级标签
    * 默认高度: 根据内容显示
    * 可以通过 CSS 调整宽和高
    * 块元素内几乎可以写任何元素
    * 常用块元素
        * h1 - h6 -- 标题, 不能相互嵌套
        * p -------- 段落, 内部不能写块标签
        * div ------ 无特殊意义
        * ol ------- 有序列表
        * ul ------- 无序列表
        * dl ------- 自定义列表
        * li ------- 列表项, 位于有序列表和无序列表中
        * dt ------- 术语名称, 位于自定义列表
        * dd ------- 术语描述, 位于自定义列表

* 行内元素
    * 多个块级元素共享一行, 一行排满后, 下一行继续
    * 默认宽度: 根据内容显示
    * 默认高度: 根据内容显示
    * 不能通过 CSS 调整长和宽
    * 行内元素可以写行内元素, 不能写块级元素
    * 常用行内元素
        * em ------ 文本标签, 行内元素, 斜体
        * strong -- 文本标签, 行内元素, 加粗
        * span ---- 文本标签, 行内元素, 无特殊意义

    
* 行内块元素
    * 多个块级元素共享一行, 一行排满后, 下一行继续
    * 默认宽度: 根据内容显示
    * 默认高度: 根据内容显示
    * 可以通过 CSS 调整长和宽

## 常用标签
### 超链接
* a 行内元素, 可以包含除a以外的任意标签, 包括块元素
* 常用说明
    * href="..." ------------------- 跳转链接
    * href="#..." ------------------ 跳转到锚点, 使用 id 指明锚点
    * href="#" --------------------- 跳转到顶部
    * href="" ---------------------- 跳转到顶部, 刷新界面
    * bref="js..." ----------------- 执行脚本
    * bref="tel:123456" ------------ 打电话
    * bref="nailto:123@gmail.com" -- 发邮件
    * bref="sms:10086" ------------- 发短信
    * target="_blank" -------------- 在新的标签页打开
    * target="_self" --------------- 在当前标签页打开, 默认
    * download --------------------- 下载, 添加值表明文件名称




# CSS



行内元素能写行内元素, 不能写块级元素


* 块级元素几乎可以写任何行内和块级元素
* 标签的默认效果不重要, 语义重要

## 标签
### 图片
* img 行内元素,
    src-指明路径
    alt-指明图片内容, 便于搜索引擎
    height-指明高, 像素
    width-指明宽, 像素
* jpg ----- 有损压缩 不支持透明背景 不支持动态图
* png ----- 无损压缩   支持透明背景 不支持动态图
* bmp -----   不压缩 不支持透明背景 不支持动态图 占用空间极大 --- 一般不用
* gif ----- 支持简单的透明背景, 支持动态图
* webp ---- 支持透明背景 动态图, 兼容性不太好 IE 不支持
* base64 -- 图片 -> 文本

### 表格
* table  表格
    border = "1"  单元格边框为 1 像素, 外部边框为 1  像素
    border = "10" 单元格边框为 1 像素, 外部边框为 10 像素
    width         表格宽度, 至少
    height        表格高度, 至少, 头部和脚注高度不变
    cellspacing   单元格之间的缝隙
* caption  表格标题
* thead    表格头部
    height       高度
    align="left" 水平对齐
    valign="top" 垂直对齐
* tbody  表格主体
    height       高度 -- 可能会自动调整
    align="left" 水平对齐
    valign="top" 垂直对齐
* tfoot  表格脚注
    height       高度
    align="left" 水平对齐
    valign="top" 垂直对齐
* tr 行
    height       高度
    align="left" 水平对齐
    valign="top" 垂直对齐
* th 列 -- 在 thead 中使用
    width        单元格宽度, 会影响当前列的所以元素
    height       单元格高度, 会影响当前行的所以元素
    align="left" 水平对齐
    valign="top" 垂直对齐
    colspan      跨行
    rowspan      跨列
* td 列 -- 在 tbody 和 tfoot 中使用
    同 th

### 表单
* form
    action -- 服务器地址
    method -- get post
    target -- 本页打开, 新标签打开
* input  输入, 行内元素
    type      类型, text-文本,
                    password-密码,
                    radio-单选,
                    checkbox-复选,
                    hidden-隐藏,
                    submit-提交 -- 不能添加 name 选项
                    reset-重置
                    button-普通按钮
    name      变量名称, 相同的name划分为一组
    value     默认值, 单选按钮必须填
    maxlength 最大长度
    checked   默认选项
    disabled  不能修改
* button 普通按钮, 确认, 重置 -- 不能添加 name 选项
    disabled  不能修改
* textarea 文本域, 能换行
    disabled  不能修改
* select 下拉框
    disabled  不能修改
    option -- 选项
        disabled  不能修改
        value 属性
        selected 默认选项
* label -- 获取焦点
    for -- 和 ID 关联
    建议用 label 包含
* fieldset 分组
    legend 名称

## 框架
* iframe 嵌入 行内元素
    src 源
    frameborder 边框

br  换行
hr  分割线
pre 按原文显示

## 全局属性
* id
* class 分类, 配合 css 使用
* style 样式
* dir   文字位于屏幕靠左还是靠右
* title 标题
* lang  语言

## 框架
header
footer
nav
article 文章整体
section 文章某段
aside   侧边栏






