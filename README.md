## Final experiment of Operating System Concept course at BUPT.

### How to run this project
1. create a database file using json grammar with whatever name and extension you want (**grammar is strictly limited**, shown as below)

   ```json
   {
     "Cyberpunk 2077": {
       "price": 49,
       "quantity": 2
     },
     "Milk": {
       "price": 5,
       "quantity": 7
     },
     "Pancake": {
       "price": 2,
       "quantity": 4
     }
   }
   ```

2. build binary: `make`
3. run: `./final --database the-database-you-created.json`

### TODO

- [x] basic methods for `item` repository
- [x] make methods in `item` thread-safe
- [x] serialization and deserialization of `item` using json-like formats
- [x] test code and description

### Requirements

- [x] 使用的编程语言为C/C++
- [x] 系统程序使用多线程或者多进程
- [x] 系统程序包含良好的初始化模块
- [x] 程序中包含内存管理（如避免指针未释放等内存泄露问题）
- [ ] 程序中包含进程管理（如资源占用管理）
- [x] 程序中使用了同步锁进行同步互斥
- [x] 文件系统(关键数据结构以文件存储)，用txt+分隔符的形式完成数据管理
- [x] 缓存管理（关键数据传递采用流控管理）
- [x] 小组代码风格是否统一
- [ ] 小组整体展示效果流畅

### Git commit guidelines
* **feat**: A new feature
* **fix**: A bug fix
* **docs**: Documentation only changes
* **style**: Changes that do not affect the meaning of the code (white-space, formatting, missing
  semi-colons, etc)
* **refactor**: A code change that neither fixes a bug nor adds a feature
* **perf**: A code change that improves performance
* **test**: Adding missing or correcting existing tests
* **chore**: Changes to the build process or auxiliary tools and libraries such as documentation
  generation