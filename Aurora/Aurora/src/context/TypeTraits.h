#ifndef TYEP_TRAITS_H_
#define TYEP_TRAITS_H_

namespace aurora
{
	template<typename _Type>
	struct TypeTraits
	{
		using Type = _Type;
		using RefType = _Type&;
		using PointerType = _Type*;
	};

	// ͨ�����û�ȡ��ʵ����
	template<typename _Type>
	struct TypeTraits<_Type&>
	{
		using Type = _Type;
		using RefType = _Type & ;
		using PointerType = _Type * ;
	};

	// ͨ��ָ���ȡ��ʵ����
	template<typename _Type>
	struct TypeTraits<_Type*>
	{
		using Type = _Type;
		using RefType = _Type & ;
		using PointerType = _Type * ;
	};
}

#endif
