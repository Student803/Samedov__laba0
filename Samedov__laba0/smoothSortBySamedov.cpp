#include<iostream>
#include<vector>
using namespace std;

#define UP_Samedov(IA,IB) temp = IA; IA += IB + 1; IB = temp;
#define DOWN_Samedov(IA,IB) temp = IB; IB = IA - IB - 1; IA = temp;


bool IsSorted_Samedov(int a, int b)
{
	return a < b ? true : false;
}

template <typename T>
void Sift_Samedov(int& root1, int& baseStretch1, int& companionStretch1, vector<T>& A)
{
	int r0, r2, temp;
	int t;
	r0 = root1;
	t = A[r0];

	while (baseStretch1 >= 3)
	{
		r2 = root1 - baseStretch1 + companionStretch1;

		if (!IsSorted_Samedov(A[root1 - 1], A[r2]))
		{
			r2 = root1 - 1;
			DOWN_Samedov(baseStretch1, companionStretch1);
		}

		if (IsSorted_Samedov(A[r2], t))
		{
			baseStretch1 = 1;
		}
		else
		{
			A[root1] = A[r2];
			root1 = r2;
			DOWN_Samedov(baseStretch1, companionStretch1);
		}
	}

	if (root1 - r0)
		A[root1] = t;
}

template <typename T>
void Trinkle_Samedov(int& leoHeapPlan, int& baseStretch1, int& H1Size, int& H2Size, int& root1, int& companionStretch1, vector<T>& A)
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
			UP_Samedov(baseStretch1, companionStretch1)
		}

		r3 = root1 - baseStretch1;

		if ((p1 == 1) || IsSorted_Samedov(A[r3], t))
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

					if (!IsSorted_Samedov(A[root1 - 1], A[r2]))
					{
						r2 = root1 - 1;
						DOWN_Samedov(baseStretch1, companionStretch1);
						p1 <<= 1;
					}
					if (IsSorted_Samedov(A[r2], A[r3]))
					{
						A[root1] = A[r3]; root1 = r3;
					}
					else
					{
						A[root1] = A[r2];
						root1 = r2;
						DOWN_Samedov(baseStretch1, companionStretch1);
						p1 = 0;
					}
				}
			}
		}
	}

	if (r0 - root1)
		A[root1] = t;

	Sift_Samedov(root1, baseStretch1, companionStretch1, A);
}

template <typename T>
void SemiTrinkle_Samedov(int& root1, int& rightMostElementOfUnsortedList, int& H2Size, int& baseStretch1, int& companionStretch1, int& leoHeapPlan, int& H1Size, vector<T>& A)
{
	int K;
	root1 = rightMostElementOfUnsortedList - H2Size;

	if (!IsSorted_Samedov(A[root1], A[rightMostElementOfUnsortedList]))
	{
		K = A[rightMostElementOfUnsortedList];
		A[rightMostElementOfUnsortedList] = A[root1];
		A[root1] = K;
		Trinkle_Samedov(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);
	}
}

template <typename T>
void smoothSortBySamedov(vector<T>& A)
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
			Sift_Samedov(root1, baseStretch1, companionStretch1, A);
			leoHeapPlan = (leoHeapPlan + 1) >> 2;
			UP_Samedov(H1Size, H2Size);
			UP_Samedov(H1Size, H2Size);
		}

		else if ((leoHeapPlan & 3) == 1)
		{
			if (unsortedListLength + H2Size < N)
			{
				int baseStretch1 = H1Size;
				int companionStretch1 = H2Size;
				Sift_Samedov(root1, baseStretch1, companionStretch1, A);
			}
			else
			{
				Trinkle_Samedov(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);
			}

			DOWN_Samedov(H1Size, H2Size);
			leoHeapPlan <<= 1;

			while (H1Size > 1)
			{
				DOWN_Samedov(H1Size, H2Size);
				leoHeapPlan <<= 1;
			}

			leoHeapPlan++;
		}

		unsortedListLength++;
		rightMostElementOfUnsortedList++;
	}

	int root1 = rightMostElementOfUnsortedList;
	Trinkle_Samedov(leoHeapPlan, baseStretch1, H1Size, H2Size, root1, companionStretch1, A);

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
				UP_Samedov(H1Size, H2Size);
			}
		}
		else
		{
			if (H1Size >= 3) {
				leoHeapPlan--;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList - H1Size + H2Size;
				if (leoHeapPlan > 0)
					SemiTrinkle_Samedov(root1, rightMostElementOfUnsortedList, H2Size, baseStretch1, companionStretch1, leoHeapPlan, H1Size, A);

				DOWN_Samedov(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList + H2Size;
				SemiTrinkle_Samedov(root1, rightMostElementOfUnsortedList, H2Size, baseStretch1, companionStretch1, leoHeapPlan, H1Size, A);
				DOWN_Samedov(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
			}
		}
	}
}

vector<int> smooth_Samedov(vector<int> data)
{
	smoothSortBySamedov(data);
	return data;
}
