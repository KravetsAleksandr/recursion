//
//  main.cpp
//  Fill in the gap
//
//  Created by Aleksandr Kravets on 8/27/18.
//  Copyright © 2018 Aleksandr Kravets. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std ;


void Paint(int, int, vector < vector <int> >&);
void Show(vector < vector <int> >&);

struct folder
{
    string name;
    bool isFile;
    std::list< std::shared_ptr<folder> > folderListPtr;
};

void FileSearch(string, const std::shared_ptr<folder>);
std::list < std::shared_ptr<string> > pathSet;
string globalPath;
int totalCallCounter = 0;



int main(int argc, const char * argv[]) {

    
// ПАПКА №1
    std::shared_ptr<folder> file111 = std::make_shared<folder>();
    file111->name = "file to be found";
    file111->isFile = true;
    
    std::shared_ptr<folder> file112 = std::make_shared<folder>();
    file112->name = "another file";
    file112->isFile = true;
    
    std::shared_ptr<folder> cat11 = std::make_shared<folder>();
    cat11->name = "FOLDER 1.1";
    cat11->isFile = false;
    cat11->folderListPtr.push_back(file111);
    cat11->folderListPtr.push_back(file112);
    
    std::shared_ptr<folder> cat12 = std::make_shared<folder>();
    cat12->name = "FOLDER 1.2";
    cat12->isFile = false;

    std::shared_ptr<folder> cat1 = std::make_shared<folder>();
    cat1->name = "FOLDER 1";
    cat1->isFile = false;
    cat1->folderListPtr.push_back(cat11);
    cat1->folderListPtr.push_back(cat12);
   
 
// ПАПКА №2
    std::shared_ptr<folder> file211 = std::make_shared<folder>();
    file211->name = "file to be found";
    file211->isFile = true;
    
    std::shared_ptr<folder> cat21 = std::make_shared<folder>();
    cat21->name = "FOLDER 2.1";
    cat21->isFile = false;
    cat21->folderListPtr.push_back(file211);
    
    std::shared_ptr<folder> file222 = std::make_shared<folder>();
    file222->name = "file to be found";
    file222->isFile = true;
    
    std::shared_ptr<folder> cat22 = std::make_shared<folder>();
    cat22->name = "FOLDER 2.2";
    cat22->isFile = false;
    cat22->folderListPtr.push_back(file222);
    
    std::shared_ptr<folder> cat2 = std::make_shared<folder>();
    cat2->name = "FOLDER 2";
    cat2->isFile = false;
    cat2->folderListPtr.push_back(cat21);
    cat2->folderListPtr.push_back(cat22);
 
   
// КОРНЕВОЙ КАТАЛОГ
    std::shared_ptr<folder> catalogue = std::make_shared<folder>();
    catalogue->name = "ROOT";
    catalogue->isFile = false;
    catalogue->folderListPtr.push_back(cat1);
    catalogue->folderListPtr.push_back(cat2);

    
    FileSearch("file to be found", catalogue);
    
    cout<<endl<<totalCallCounter<<" total call counter"<<endl;
    cout<<endl<<pathSet.size()<<" file(s) were found"<<endl<<endl;
    for (auto ptr : pathSet)
    {
        cout<<(*ptr)<<endl;
    }
    
    
    
    const int matrix_size = 6;
    vector < vector <int> > myMatrix(matrix_size, vector<int>(matrix_size, 1)); //filled with 1
    myMatrix.at(1).at(1) =
    myMatrix.at(1).at(2) =
    myMatrix.at(2).at(1) =
    myMatrix.at(2).at(2) =
    myMatrix.at(2).at(3) =
    myMatrix.at(2).at(4) =
    myMatrix.at(3).at(1) =
    myMatrix.at(3).at(2) =
    myMatrix.at(4).at(2) = 0;
    
    cout<<"Initial:";
    Show(myMatrix);
    
    Paint(4, 2, myMatrix);
   
    cout<<endl<<endl<<"Result:";
    Show(myMatrix);

    return 0;
}


void FileSearch(string fileName, const std::shared_ptr<folder> currentFolder)
{
    
    totalCallCounter++;

    // Если каталог с пустыми ссылками или файл с другим именем - выходим
    if ( (currentFolder->isFile == false && currentFolder->folderListPtr.empty()) ||
        (currentFolder->isFile == true && currentFolder->name != fileName) )
        return;
    
    // Записываем путь по которому движемся
    globalPath += currentFolder->name + "/";
    
    // Проходимся по ссылкам каталога вызывая рекурсивно каждую из них
    if ( currentFolder->isFile == false )
    {
        for (auto it = currentFolder->folderListPtr.begin(); it != currentFolder->folderListPtr.end(); ++it)
        {
            FileSearch("file to be found", (*it));
        }
    }
    // Если найден файл по искомому имени сохраняем полный путь
    else if ( currentFolder->isFile == true && currentFolder->name == fileName )
        {
            std::shared_ptr<string> sptr = std::make_shared<string>();
            (*sptr) = globalPath;
            (*sptr).pop_back();
            (*sptr) += "\n";
            pathSet.push_back(sptr);
        }
   
    //Завершив поиск по ветке удаляем запись пути перед откатом назад
    globalPath.pop_back();
    globalPath.erase (globalPath.end() - currentFolder->name.length(), globalPath.end());
    
    return;
}





void Paint (int row, int col, vector < vector <int> >& myMatrix)
{
    
    // добавить проверку на выпадение из размерности матрицы
    // проверить возможные частные случаи
    
    myMatrix.at(row).at(col) = 5;
    Show(myMatrix);
    
    if( myMatrix.at(row + 1).at(col) == 0 )
    {
        Paint(row + 1, col, myMatrix);
    }

    if( myMatrix.at(row - 1).at(col) == 0 )
    {
        Paint(row - 1, col, myMatrix);
    }
    
    if( myMatrix.at(row).at(col + 1) == 0 )
    {
        Paint(row, col + 1, myMatrix);
    }
    
    if( myMatrix.at(row).at(col - 1) == 0 )
    {
        Paint(row, col - 1, myMatrix);
    }
    
    return;
}

void Show(vector < vector <int> >& myMatrix)
{
    cout<<endl;
    for(auto &row : myMatrix)
    {
        for(int col = 0; col < row.size(); col++)
        {
            cout<<row[col]<<"\t";
        }
        cout<<endl;
    }
}
