## TableMaker

从data.in文件读入 格式如下

$cnt$(场次)

$n$(题目数量)

$Task_1$ $Score/Rating_1$ $Solver_1$

...

$Task_n$ $Score/Rating_n$ $Solver_n$

生成markdown表格 效果如下

|    Solver    |               -                |               -                |               -                |               -                |
| :----------: | :----------------------------: | :----------------------------: | :----------------------------: | :----------------------------: |
|     Task     | <a href="#CFxxxxA">CFxxxxA</a> | <a href="#CFxxxxB">CFxxxxB</a> | <a href="#CFxxxxC">CFxxxxC</a> | <a href="#CFxxxxD">CFxxxxD</a> |
| Score/Rating |              1200              |              1300              |              1600              |              1900              |
|     Tag      |                                |                                |                                |                                |

### <a name="CFxxxxA">CFxxxxA</a>

### <a name="CFxxxxB">CFxxxxB</a>

### <a name="CFxxxxC">CFxxxxC</a>

### <a name="CFxxxxD">CFxxxxD</a>