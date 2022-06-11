#ifndef VECTORHPP
#define VECTORHPP

template <typename T>
class Vector {
	public:
		Vector();
		Vector(int size);
		~Vector();

		T * getItems();
		int accessVector();
		void writeElement(T item);
		T readElement(int pos);
		void printVector();
		void bubbleSort();

	private:
		int key;
        static int current_key;
		T * items;
		int position;
		int size;

	friend class Card;
	friend class Player;
	friend class Round;
};

#endif 