#include <string>
using std::string;
class ProgressBar;

class FileSplitter
{
	string m_filePath;
	int m_fileNumber;
	ProgressBar* m_progressBar;

public:
  FileSplitter(const string &filePath, int fileNumber, ProgressBar *progressBar)
      : m_filePath(filePath), m_fileNumber(fileNumber),
        m_progressBar(progressBar) {}

  void split() {
    for (int i = 0; i < m_fileNumber; i++) {
      float progressValue = m_fileNumber;
      progressValue = (i + 1) / progressValue;
      m_progressBar->setValue(progressValue);
    }
  }
};