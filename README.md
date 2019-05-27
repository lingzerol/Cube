# Cube
Auto-restoring magic cube
=========================

一个魔方还原程序，使用了Z-Buffer算法和简单光照模型，能显示魔方的3D结构，并使用了层先法还原魔方，能根据输入指令的不同对模仿进行操作

功能
-----

该程序能显示魔方的3D结构，但是里面的3D模型降2D的算法可以直接拿出来使用，不局限于魔方显示。同时，对魔方的操作以指令形式进行操作，共分为22种指令，分别对应魔方的不同操作。

项目的基本结构
-------------

Cube.h、Cube.cpp: 用于实现3D模型转2D图像，并增加光照模型  
Magic_Cube.h、Magic_Cube.cpp: 包含魔方还原的函数及类

程序效果
--------

![image](https://raw.githubusercontent.com/lingzerol/Cube/master/Program%20performance/cube_restoring.PNG)