# 前言
　　该文章是我在2016年的时候发布在电子发烧友论坛上面的，但是还是在校大学生，没有个人博客，现在搭建了一个个人博客，所以就把文章转到了个人博客上了。该文章在电子发烧友上的链接：[[经验] 51单片机的音乐盒(c语言)](http://bbs.elecfans.com/jishu_1102723_1_1.html "[经验] 51单片机的音乐盒(c语言)")
  
# 背景
　　以前也用各种单片机做个一些东西，但都没想过发帖，最近比较关注这个论坛，所以也来发过帖子玩玩。
  
　　到期末了。这学期学了单片机这门课，用的是汇编语言，但是说实话，学了一个学期的汇编语言，对汇编语言还是不太会用。期末了要单片机的实验考试，老师要求可以做一个音乐盒或者汉字点阵就免考，虽然考试也很简单，但是我还是决定做一个实物，显得"高大上",本人大一的时候就学会了C语言对单片机的编程，这次课程设计当然也要用C语言来完成了。
   
　　最开始本来是想做一个显示汉字的点阵的，但是网上一搜电路图，太复杂了，如果要显示汉字就必须要使用4块8*8的点阵，电路图复杂的可怕，如果要手焊的话，估计每个两三天完成不了，本着简单快速的原则，我就做一个音乐盒算了。
  
　　既然想好了做音乐盒，接下来就是准备元器件了，要用到的元器件有：1602液晶，52单片机，,按键，各种电容，电阻，三极管，无源蜂鸣器等，是不是废话有点多了，哈哈...
  
# 电路设计
　　音乐盒所要用到的原理图都是我从网上搜的，所以与我所做的实物的线路连接还是有一些区别的，还是贴一下图吧。
## 52单片机最小系统板电路图　
![51单片机最小电路](https://github.com/hehung/51_music_player/blob/master/img/51%E5%8D%95%E7%89%87%E6%9C%BA%E6%9C%80%E5%B0%8F%E7%94%B5%E8%B7%AF.jpg?raw=true "51单片机最小电路")
## 1602液晶电路图
![LCD1602液晶屏电路](https://github.com/hehung/51_music_player/blob/master/img/LCD1602%E6%B6%B2%E6%99%B6%E5%B1%8F%E7%94%B5%E8%B7%AF.jpg?raw=true "LCD1602液晶屏电路")

## 蜂鸣器驱动电路图
![蜂鸣器驱动电路](https://github.com/hehung/51_music_player/blob/master/img/LCD1602%E6%B6%B2%E6%99%B6%E5%B1%8F%E7%94%B5%E8%B7%AF.jpg?raw=true "蜂鸣器驱动电路")

## 按键电路图
![按键电路设计](https://github.com/hehung/51_music_player/blob/master/img/%E8%9C%82%E9%B8%A3%E5%99%A8%E9%A9%B1%E5%8A%A8%E7%94%B5%E8%B7%AF.jpg?raw=true "按键电路设计")

　　 这里有两种案件的连接方式，我采用的是第一种，这样写程序的时候，当按键按下时，相应的IO口就会变成低电平，而第二种相应的IO口会变成高电平。

# 电路焊接
　　接下来就开始焊接了，但是我是在吧实物做好了之后才想起来要发帖的，所以焊接的过程就yy一下就行了....其实焊接的过程很简单，花了我一个下午加晚上的时间，不要问我为什么花费这么久，看图。
  
先上一张正面图

![完成作品正面](https://github.com/hehung/51_music_player/blob/master/img/%E5%AE%8C%E6%88%90%E4%BD%9C%E5%93%81%E6%AD%A3%E9%9D%A2.jpg?raw=true "完成作品正面")

背面图

![完成作品背面图](https://github.com/hehung/51_music_player/blob/master/img/%E5%AE%8C%E6%88%90%E4%BD%9C%E5%93%81%E8%83%8C%E9%9D%A2%E5%9B%BE.jpg?raw=true "完成作品背面图")

# 引脚连接
　　背面的电路图看着有点乱，但是仔细焊接的话，还是不复杂的。
　　你们可能会疑惑我为什么会加一排LED灯，那是我无聊加上的，用来配合音乐播放时的节拍，很low.......haha
下面说一下我的实物图的接线
＝＝》蜂鸣器-------->P1^3
＝＝》暂停按键------>P3^7，按下暂停后会在右上角显示pause，表示已经暂停了
＝＝》下一首按键---->P3^6
＝＝》上一首按键---->P3^5
　　这样就完成了，其实做的这个还是很low的，实在无聊就发个帖子玩玩。

# 成品展示
　　说一下缺陷：这个蜂鸣器有个毛病，就是声音大了就很有很多杂音，最开始的时候本来没串接电阻，声音是很大，只不过杂音太大了，基本上听不到音乐，之后接了一个大一点的电阻，音乐是有了，但是声音又太小了，没办法，我就串接了一个电位器，可以用来调节音量的大小，但是声音大了还是会有杂音。所以最好还是有个喇叭。

　　在附几张图。我用的是1602，不能显示中文（能显示，只不过没花时间去弄，期末了，要复习），如果想方便显示中文的话害的要一个12864液晶，显示中文很方便。
  
  ![成品展示１](https://github.com/hehung/51_music_player/blob/master/img/%E6%88%90%E5%93%81%E5%B1%95%E7%A4%BA%EF%BC%91.jpg?raw=true "成品展示１")

　　来张动态图

![成品展示２](https://github.com/hehung/51_music_player/blob/master/img/%E6%88%90%E5%93%81%E5%B1%95%E7%A4%BA%EF%BC%92.gif?raw=true "成品展示２")



