import os

def deleteFiles(path):
    for nameFile in os.listdir(path):
        newPath = path + "/" + nameFile
        if os.path.isdir(newPath + "/"):
            #print("Go to:",newPath)
            deleteFiles(newPath)
        else:
            if(newPath[-2:] == '.o'):
                print(newPath)
                os.remove(newPath)

currentPath = os.getcwd()

deleteFiles(currentPath)
