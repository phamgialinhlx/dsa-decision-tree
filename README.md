# Decision Tree - DSA Assignment

## Introduction

**Decision Tree** is an assignment in the **Data structure and Algorithms** (*DSA*) Course of UET (***University of Engineering and Technology***).  
The lecturer of this course: **BSc. Pham Dinh Tuan**.

## Usage

### Input

The basic input is **Data** which have 4 attributes called `<att1>, <att2>, <att3>, <att4>` and 1 label which can be L (*left*), R (*right*) và B (*balance*).  
Input data is splited into three different parts:  
- The **training part** is file [`train.txt`]() which is being used to train the decision tree.  
- The **public test** is file [`valid.txt`]() which is being used to test the prediction of the tree. All the data in **valid** have its own label, so we can check if our tree had predicted the right lable of each data.  
- The **private test** is file [`private.txt`]() which is being used to test the prediction of the tree and the answer is given to our lecturer for assignment's score. Note that all the data in **private** don't have its own label!  

### Output

The basic output is **Label** of one prediction based on 4 attributes in the basic data. Our goal is building a decision tree which can predict the **Label** of a given **Data** and improve the prediction accuracy of the tree.  
Output data is splited into two parts:
- The **output** is file [`outputFromTerminal`]() which has the best output prediction accuracy of the tree that we had tested since the project started.  
- The **private answer** is file [`result.txt`]() which contains the answer for the **private test**.  
- The **saved tree** is file [`savedData.txt`]() which contains the data is exported from tree and can be import to build a tree. We store the best model of decision tree in this file!

### Tree details

Decision tree is being used to predict label based on 4 given attributes. It can be L or R or B. There are two things we need to know when we are building or training a decision tree. They are:  
- `max depth` is the **highest level of the tree**.  
- `min size` is the **minimum size that a node in tree can contain**.  

When evaluate a tree, we notice two things (or three in this project):
- **The accuracy of trainData** - this is the accuracy of the prediction when we used tree to predict the label of the trainData (`train.txt`).  
- **The accuracy of validData** - this is the accuracy of the prediction when we used tree to predict the label of the validData (`valid.txt`).  
- **The accuracy of testData** - Just like two things above, but the testData is a new data that has been created for this project.

### How to run it?

Download the source file (as .zip). Extract to a folder and open `cmd` in that folder.   
To run the program just paste this line to `cmd` and hit `Enter`:
```cmd
g++ -std=c++17 AdaBoost.cpp Stump.cpp BitMask.cpp Console.cpp CostCalc.cpp Data.cpp DecisionNode.cpp Node.cpp SplitData.cpp TerminalNode.cpp TestGenerator.cpp Tree.cpp RandomForest.cpp Client.cpp -o Client
```
After hit `Enter`, it create a new file called `Client.exe`. You can run it by double click the file or simply paste this line to `cmd` and hit `Enter` again:
```cmd
.\Client.exe 
```
If you dont't want to see the output in `cmd`, you can use this line: 
```cmd
.\Client.exe > outputFromTerminal.txt
```
After hit `Enter`, it create a new file called `outputFromTerminal.txt` contains the ouput in a txt file.

### Cmd UI

## Updates

### Update 1 - Design API

Create several basic file:  
- [`Client.cpp`]() is the file contains main function. In the future, it become the GUI to using the program.  
- [`Data.h`]() and `struct Data`. This is the basic data and basic unit of the tree.
- [`Node.h`]() and `struct Node`. Node of a tree and some function to caculate GiniIndex.
- [`TestGenerator.h`]() this is a library which is designed exclusively for this project. Generate testData.
- [`Tree.h`]() and `struct tree`. Basic struct tree. 

### Update 2 - Completed some bacsic struct.

In this update, we completed the API and make a new function to caculate `EntropyIndex`.
- `struct Data` is completed.
- `giniIndex` caculate function is completed.
- Some split data into two group function are completed.
- `entropyIndex` caculate function is completed.

After this update, the project will bigger and we'll need to organize the file and structure more clearly.

### Update 3 - Finished `split data` + `bit mask` + `cost calc`

So in this update, we split the file in to multiple header files. They are:
- `splitData.h` contains `namespace splitData`. This namespace contains functions that split data into two group based on attributes.  
- `bitMask.h` is the header contains function to check if the bit in the given index of a number is 1.
- `costCalc.h` is the header contains function to caculate `giniIndex` and `entropyIndex`.

### Update 4 - Completed buildTree and printTree

In this update, we had successfully build decision tree and print it out the cmd terminal. Also, fixed some bugs about memory and debugger.  

One thing is this update is so big that because we found trouble when coding with only header file (`.h`) but not include and split it to two file `.cpp` and `.h`. So we have to split it out and organize the project again. Finally, the project is very clearly and there are a lot of file in the source folder xD.  

After this update, we need predict function and we can started caculate the accuracy of the tree.

### Update 5 - Predict and future improve

In this update, we completed the predict function and started predict the label of validData.  
<!-- Note the prediction result here! -->

So because the prediction result is low and we are not satisfy with that. So my teammate has done some research and found that we could imporve the tree by adding [`Random forrest`](). You can see more about this in that link.

### Update 6 - Random forrest

`Random forrest` is basically a forrest that contains a lot of decision tree in it. So what make it improve our prediction result?   

So the first thing that we notice is the label **'B'** is the most difficult prediction. And luckily `Random forrest` is good to against this trouble. By randomly generate some boost trap data with have more label **'B'** in it and then build a decision tree based on that dataset. By repeating that process, we have create a forrest that can predict label **'B'** better.

But the more we build a new tree, the more slowly it is. So we have to limit size of forrest down to 100 trees. 

<!-- Note the prediction result here! -->

By boosting the label **'B'** and randomly create several tree, we have created some very best model in the upcomming update.

### Update 7 - Upgrade random forrest and fixed some bugs

In this update, we notice that the way we build random forrest is not the best option. So, we have upgrade it by two ways:  
- Build the forrest by try `max depth` and `min size` (apply to all tree in the forrest) to find the best model which has the best accuracy when predict the `trainData`.
- Build the tree by try `max depth` and `min size` to find the best tree which has the best accuracy when predict the `trainData` or `validData` and repeat that process to make the forrest.

By doing like that, we have created some best model which has stunning result:

<!-- Note the prediction result here! -->

Also, in this update, we have created two new functions for tree which are `import()` and `export()`. By using they, we can store our best model to file and keep it safe.  

### Update 8 - Ada boost

<!-- Nổ súng đi Linh! -->

<!-- Note the prediction result here! -->

## Issues

We are not create list of Known Issues because of the limited time.  
But if you found a bug or have a new idea for this project, you can contact to us (by mail).

## Support

You can ask for help in:
- Support email 1: 20020001@vnu.edu.vn
- Support email 2: phamgialinhlx@gmail.com

## Authors

This project is being developed by:
- [**Bá Lương**](https://github.com/20020001-UET)
- [**Gia Linh**](https://github.com/phamgialinhlx)

## Credits

Thanks to third-party open source projects, to contributors, and all the people who have contributed ideas, patches, bugs report, feature requests, donations, and help me to develop this project.

Last but not least, thanks to our lecturer - **Pham Dinh Tuan** who gave us this problem and resource to research and develop this project! 