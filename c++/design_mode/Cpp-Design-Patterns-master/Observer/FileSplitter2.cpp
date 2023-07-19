#include <list>
#include <string>

using std::string, std::list;

class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};


class FileSplitter
{
	string m_filePath;
	int m_fileNumber;

        list<IProgress *> m_iprogresslist;

      public:
        FileSplitter(const string &filePath, int fileNumber)
            : m_filePath(filePath), m_fileNumber(fileNumber) {}

        void split() {
          for (int i = 0; i < m_fileNumber; i++) {
            float progressValue = m_fileNumber;
            progressValue = (i + 1) / progressValue;
            onProgress(progressValue);
          }
        }

        void addIProgress(IProgress *iprogress) {
          m_iprogresslist.push_back(iprogress);
        }

        void removeIProgress(IProgress *iprogress) {
          m_iprogresslist.remove(iprogress);
        }

protected:
	virtual void onProgress(float value){
          list<IProgress *>::iterator itor = m_iprogresslist.begin();
          while (itor != m_iprogresslist.end())
            (*itor)->DoProgress(value);
          itor++;
        }
};