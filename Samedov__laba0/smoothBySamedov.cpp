#include<iostream>
#include<vector>
using namespace std;

#define UP(IA,IB) temp = IA; IA += IB + 1; IB = temp;
#define DOWN(IA,IB) temp = IB; IB = IA - IB - 1; IA = temp;


inline bool IsSorted(int a, int b)
{
	return a < b ? true : false;
}


inline void Sift(int& root1, int& baseStretch1, int& companionStretch1, vector<int>& A)
{
	int r0, r2, temp;
	int t;
	r0 = root1;
	t = A[r0];

	while (baseStretch1 >= 3)
	{
		r2 = root1 - baseStretch1 + companionStretch1;

		if (!IsSorted(A[root1 - 1], A[r2]))
		{
			r2 = root1 - 1;
			DOWN(baseStretch1, companionStretch1);
		}

		if (IsSorted(A[r2], t))
		{
			baseStretch1 = 1;
		}
		else
		{
			A[root1] = A[r2];
			root1 = r2;
			DOWN(baseStretch1, companionStretch1);
		}
	}

	if (root1 - r0)
		A[root1] = t;
}


inline void push(int i, vector<int>& A)
{
	A.push_back(i);
}

//
inline void Trinkle(int& leoHeapPlan, int& baseStretch1, int& H1Size, int& H2Size, int& root1, int& companionStretch1, vector<int>& A)
{
	int p1, r2, r3, r0, temp;
	int t;
	p1 = leoHeapPlan;
	baseStretch1 = H1Size;
	companionStretch1 = H2Size;
	r0 = root1;
	t = A[r0];

	while (p1 > 0)
	{
		while ((p1 & 1) == 0)
		{
			p1 >>= 1;
			UP(baseStretch1, companionStretch1)
		}

		r3 = root1 - baseStretch1;

		if ((p1 == 1) || IsSorted(A[r3], t))
		{
			p1 = 0;
		}
		else
		{
			--p1;
			if (baseStretch1 == 1)
			{
				A[root1] = A[r3];
				root1 = r3;
			}
			else
			{
				if (baseStretch1 >= 3)
				{
					r2 = root1 - baseStretch1 + companionStretch1;

					if (!IsSorted(A[root1 - 1], A[r2]))
					{
						r2 = root1 - 1;
						DOWN(baseStretch1, companionStretch1);
						p1 <<= 1;
					}
					if (IsSorted(A[r2], A[r3]))
					{
						A[root1] = A[r3]; root1 = r3;
					}
					else
					{
						A[root1] = A[r2];
						root1 = r2;
						DOWN(baseStretch1, companionStretch1);
						p1 = 0;
					}
				}
			}
		}
	}

	if (r0 - root1)
		A[root1] = t;

	Sift(root1, baseStretch1, companionStretch1, A);
}


inline void SemiTrinkle(int& root1, int& rightMostElementOfUnsortedList, int& H2Size, int& baseStretch1, int& companionStretch1, int& leoHeapPlan, int& H1Size, vector<int>& A)
{
	int T;
	root1 = rightMostElementOfUnsortedList - H2Size;

	if (!IsSorted(A[root1], A[rightMostElementOfUnsortedList]))
	{
		T = A[rightMostElementOfUnsortedList];
		A[rightMostElementOfUnsortedList] = A[root1];
		A[root1] = T;
		Trinkle(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);
	}
}

inline void SmoothSorting(vector<int>& A)
{
	const int N = A.size();
	int temp;
	int unsortedListLength = 1;
	int rightMostElementOfUnsortedList = 0;
	int leoHeapPlan = 1;
	int H1Size = 1;
	int H2Size = 1;
	int baseStretch1 = 0;
	int companionStretch1 = 0;
	while (unsortedListLength < N)
	{
		int root1 = rightMostElementOfUnsortedList;
		if ((leoHeapPlan & 7) == 3)
		{
			int baseStretch1 = H1Size;
			int companionStretch1 = H2Size;
			Sift(root1, baseStretch1, companionStretch1, A);
			leoHeapPlan = (leoHeapPlan + 1) >> 2;
			UP(H1Size, H2Size);
			UP(H1Size, H2Size);
		}

		else if ((leoHeapPlan & 3) == 1)
		{
			if (unsortedListLength + H2Size< N)
			{
				int baseStretch1 = H1Size;
				int companionStretch1 = H2Size;
				Sift(root1, baseStretch1, companionStretch1, A);
			}
			else
			{
				Trinkle(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);
			}

			DOWN(H1Size, H2Size);
			leoHeapPlan <<= 1;

			while (H1Size > 1)
			{
				DOWN(H1Size, H2Size);
				leoHeapPlan <<= 1;
			}

			leoHeapPlan++;
		}

		unsortedListLength++;
		rightMostElementOfUnsortedList++;
	}

	int root1 = rightMostElementOfUnsortedList;
	Trinkle(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);

	while (unsortedListLength > 1)
	{
		--unsortedListLength;

		if (H1Size == 1)
		{
			rightMostElementOfUnsortedList--;
			leoHeapPlan--;

			while ((leoHeapPlan & 1) == 0)
			{
				leoHeapPlan >>= 1;
				UP(H1Size, H2Size);
			}
		}
		else
		{
			if (H1Size >= 3) {
				leoHeapPlan--;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList - H1Size + H2Size;
				if (leoHeapPlan > 0)
					SemiTrinkle(root1, rightMostElementOfUnsortedList, H2Size, baseStretch1, companionStretch1, leoHeapPlan, H1Size, A);

				DOWN(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList + H2Size;
				SemiTrinkle(root1, rightMostElementOfUnsortedList, H2Size, baseStretch1, companionStretch1, leoHeapPlan, H1Size, A);
				DOWN(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
			}
		}
	}
}
