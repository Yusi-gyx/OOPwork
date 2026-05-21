# 代码审阅

## 正确性问题

1. *Playlist::removeByArtist*函数中调用了*erase*函数来删除*vector*中的迭代器，但是在删除之后会发生迭代器失效，使得第一次删除后循环无法进行
2. *Playlist::getPlayCount*函数被定义为常量函数，而map重载的[]不是常量函数，不能在这个函数中调用。应该使用有const重载版本的at()或者用find()查找
3. *Playlist::generateRecommendations*函数中在遍历的过程中不断向vector中添加对象，这可能会导致迭代器失效
4. *MusicLibrary::importSong*函数中两个智能指针都是通过裸指针定义的，这回导致指针重复释放
5. *transferSong*函数中std::move(song)之后，song内的指针已经被移走了，再调用song->display()是空指针解引用

## 运行效率问题

1. 在*addSong*函数中push_back函数中可以通过std::move直接将智能指针转移，避免复制开销

## 设计合理性问题

1. 其实这个程序中没有必要使用智能指针，并不会出现多个指针指向同一地址的问题，可以使用普通指针或者引用
