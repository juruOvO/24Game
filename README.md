# 24Game
## 这是对大作业文件的说明
0. 提交文件结构：
    - /24Game下为源代码
    - /others下为相关截图
    - /release下为编译好的文件，通过快捷方式可以直接运行应用程序。实际exe文件在/release/Application/release/release/24Game.exe
1. 使用工具：
    与先前提交的描述不同的是，大作业中实际使用的图形库是Qt，这是考虑到OpenGL在GUI开发中存在功能过剩的问题。
2. 实现功能：
    功能的截图演示在/others文件夹中。
    2.1 核心功能：24点计算
    2.2 针对文件的操作
    2.3 历史记录功能
    2.4 重试功能
    2.5 用户交互界面
    此前描述中提及的线上功能，考虑到课程要求、实际开发时间等因素，只进行了GUI设计，并未进行实际功能开发。经过思考，使用Qt的QtcpServer与QtcpSocket库，可以通过TCP/IP协议实现P2P联机功能。
3. 运行环境说明：
    3.1 有关开发环境的说明
        本次大作业开发环境为
        - Windows 11 (64-bit)
        - Qt 6.8.1
        - MinGW 13.1.0 (64-bit)
    3.2 测试环境说明
        为避免搭建环境的麻烦，提交文件中提供了可以直接在Windows平台上运行的可执行文件，可以在/release下找到该文件的快捷方式运行。
        如需重新构建代码，请确保运行环境中有Qt开发环境。
4. 文件功能测试方法：
    本程序提供了简单的文件测试方法。在程序主窗口中点击"Browse..."按钮，选择测试所用.txt文件，之后程序将自动输出结果到原来的.txt文件中（即覆盖选择的.txt文件内容），操作完成后会跳出弹窗。建议在测试时复制一份.txt文件，避免意外覆盖原文件。
