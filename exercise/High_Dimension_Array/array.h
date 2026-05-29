#pragma once
#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
using namespace std;

template<class T, int N>
class MultiArray {
	//在这里进行友元类声明，在成员函数中可以使用其他类的私有成员
	template<class otherT, int otherN>
	friend class MultiArray; 
private:
	//注意：成员声明时不能直接初始化
	vector<T> arr;
	vector<int> dim_record;
	//考虑：准备采用一维数组扁平化的方法把高维数组的元素映射到一维数组中去
	bool initialized = false;   //表示是否进行了初始化
public:
	MultiArray()
	{
		arr = vector<T>(0);
		dim_record = vector<int>(N, 0);
	}
	~MultiArray() {}
	MultiArray(const vector<int> &dims, const vector<T> &data = vector<T>())
	{
		dim_record = vector<int>(N, 0);
		int dims_size = dims.size();
		//如果维数信息数组为空
		if(dims_size == 0)
		{
			//记录维数
			int data_size = data.size();
			dim_record [0] = data_size;
			for(int i = 1; i < N ; i++) dim_record [i] = 1;
			//构造数组
			arr = vector<T>(data_size);
			for(int i = 0 ; i < data_size ; i ++) arr [i] = data [i];
		}
		//如果维数信息数组不够长
		else if (dims_size < N)
		{
			//记录维数
			int num = 1;
			for(int i = 0 ; i < dims_size; i ++) 
			{
				dim_record [i] = dims [i];
				num *= dims [i];
			}
			for(int i = dims_size ; i < N ; i ++) dim_record [i] = 1;
			arr = vector<T>(num);
			//如果数据数组为空
			if(data.size() == 0) for(int i = 0 ; i < num ; i ++) arr [i] = T();
			//如果数据数组不为空
			else for(int i = 0 ; i < num ; i ++) arr [i] = data [i];
		}
		//如果维数信息数组够长
		else
		{
			//记录维数
			int num = 1;
			for(int i = 0 ; i < N ; i ++)
			{
				dim_record [i] = dims [i];
				num *= dims [i];
			}
			arr = vector<T>(num);
			//如果数据数组为空
			if(data.size() == 0) 
				for(int i = 0 ; i < num ; i ++) arr [i] = T();
			//如果数据数组不为空
			else
				for(int i = 0 ; i < num ; i ++) arr [i] = data [i];
		}
		initialized = true;
	}
	void set(const vector<int> &idx, const T &val)
	{
		int pos = getDistance(idx);
		arr [pos] = val;
	}
	T& get(const vector<int> &idx)
	{
		int pos = getDistance(idx);
		return arr [pos];
	}
	vector<int>& get_dims()
	{
		return dim_record;
	}

	template<int M>
	bool operator==(const MultiArray<T, M> &other) const
	{
		if(!(initialized && other.initialized))  return false;
		if(M != N) return false;
		for(int i = 0 ; i < N ; i ++)
		{
			if(dim_record [i] != other.dim_record [i]) return false;
		}
		if(arr.size() != other.arr.size()) return false;
		for(int i = 0 ; i < arr.size(); i ++)
		{
			if(arr [i] != other.arr [i]) return false;
		}
		return true;
	}
	template<int M>
	bool operator!=(const MultiArray<T, M> &other) const
	{
		return !(*this == other);
	}
	MultiArray& operator=(const MultiArray<T, N> &other)
	{
		//如果没有初始化，即通过MultiArray()进行的初始化
		if (!initialized)   
		{
			arr = other.arr;
			dim_record = other.dim_record;
			initialized = true;
		}
		//其他情况下需要判断二者的维数是否相同
		else      
		{
			for (int i = 0; i < N; i++)
			{
				if (dim_record[i] != other.dim_record[i])
					return *this;
			}
			arr = other.arr;
		}
		return *this;
	}

	class Iterator {
		const T* p;   //这里需要声明成const，因为构造函数中传入的对象是const类型，所以使用的指针一定要保证不会更改
	public:
		Iterator(const MultiArray* Arr, int idx)
		{
			p = Arr->arr.data() + idx;
		}
		T operator*() const
		{
			return *p;
		}
		Iterator& operator++()
		{
			p ++;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator temp = *this;
			p ++;
			return temp;
		}
		bool operator!=(const Iterator& other) const
		{
			return p != other.p;
		}
		bool operator==(const Iterator& other) const
		{
			return p == other.p;
		}
		Iterator& operator=(const Iterator& other)
		{
			p = other.p;
			return *this;
		}
	};
	Iterator begin() const    //注意返回值类型和const声明
	{
		return Iterator(this, 0);
	}
	Iterator end() const
	{
		return Iterator(this , arr.size());
	}

	template<bool IsConst, int Rest>
	class IndexProxy {
	private:
		using ArrayType = std::conditional_t<IsConst, const MultiArray<T, N>, MultiArray<T, N>>;
		ArrayType* p;
		vector<int> idx_record;
	public:
		IndexProxy(ArrayType* p_, const vector<int>& idx_) : p(p_), idx_record(idx_) {}

		decltype(auto) operator[](const int &idx)
		{
			vector<int> next = idx_record;
			next.push_back(idx);
			if constexpr (Rest == 1) return (p->arr[p->getDistance(next)]);
			else return IndexProxy<IsConst, Rest - 1>(p, next);
		}

		decltype(auto) operator[](const int &idx) const
		{
			vector<int> next = idx_record;
			next.push_back(idx);
			if constexpr (Rest == 1) return (p->arr[p->getDistance(next)]);
			else return IndexProxy<IsConst, Rest - 1>(p, next);
		}
	};

	decltype(auto) operator[] (const int &idx)
	{
		if constexpr (N == 1) return (arr[idx]);
		else return IndexProxy<false, N - 1>(this, vector<int>{idx});
	}
	decltype(auto) operator[] (const int &idx) const
	{
		if constexpr (N == 1) return (arr[idx]);
		else return IndexProxy<true, N - 1>(this, vector<int>{idx});
	}

	void reshape(const vector<int> &dims2)
	{
		int curr_size = arr.size();
		//如果总容量不相同，则忽略此次操作
		int num = 1;
		for(int i = 0 ; i < dims2.size() ; i ++) num *= dims2[i];
		if(curr_size != num) return;

		dim_record = move(dims2);   //直接复制维数记录，数据没有改变
	}
	void resize(const vector<int> &dims2)
	{
		int num = 1;
		for(int i = 0 ; i < N ; i ++) num *= dims2 [i];
		vector<T> transformed(num);    //构造新的数组
		//给新数组赋值
		vector<int> idx(N, 0);
		while(idx [0] < dims2 [0])   //反向遍历给新数组赋值
		{
			//1.获得对应位置并赋值
			bool existed = true;
			for(int i = 0 ; i < N ; i ++) 
				if(idx [i] >= dim_record [i]) 
				{
					existed = false;
					break;
				}

			int pos = 0;
			for (int i = 0; i < N - 1; i++)
			{
				int num = idx[i];
				for (int j = i + 1; j < N; j++)
					num *= dims2[j];
				pos += num;
			}
			pos += idx[N - 1];
			if(existed) transformed [pos] = arr [getDistance(idx)];
			else transformed [pos] = T();
			//2.位置递增
			idx [N - 1] ++ ;
			//3.判断是否有进位
			for(int i = N - 1; i > 0 ; i --)
			{
				if(idx [i] == dims2 [i]) 
				{
					idx [i] = 0 ;
					idx [i - 1] ++;
				}
			}
		}
		arr = move(transformed);	
		dim_record = move(dims2);
	}

	int getDistance(const vector<int>  &idx) const //计算数组元素的实际位置，建立映射关系
	{
		int pos = 0 ;
		for(int i = 0 ; i < N - 1 ; i ++)
		{
			int num = idx [i];
			for(int j = i + 1 ; j < N ; j ++) num *= dim_record [j];
			pos += num;
		}
		pos += idx [N - 1];
		return pos;
	}

	template<class U, int M>
	friend std::ostream& operator<<(std::ostream &out, const MultiArray<U, M> &a);
};

template<class T, int N>
std::ostream& operator << (std::ostream &out, const MultiArray<T, N> &a)
{
	vector<int> index(N, 0);
	while (index[0] < a.dim_record[0])
	{
		out << "[";
		for (int j = 0; j < N - 1; j++) out << index[j] << "][";
		out << index[N - 1] << "] = " << a.arr[a.getDistance(index)];
		bool change_line = false;
		for(int i = 0 ; i < N ; i ++)
		{
			if(index [i] + 1 != a.dim_record [i]) 
			{
				change_line = true; 
				break;
			}
		}
		if(change_line) out << endl;
		index[N - 1]++;
		for (int i = N - 1; i > 0; --i) // 从后面向前比较，如果后面满了就进一
		{
			if (index[i] == a.dim_record[i])
			{
				index[i - 1]++;
				index[i] = 0;
			}
		}
	}
	return out;
}