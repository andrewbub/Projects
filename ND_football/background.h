// Andrew Bub and Harry Gebremedhin
// CSE 20311	Final Project
// background.h
// interface for a Background class

using namespace std;

class Background
{
	public:
		Background();
		Background(int);
		~Background();
		void setBackground(int);
		void set10();
		void set20();
		void set30();
		void over();
	private:
		int level;
};
