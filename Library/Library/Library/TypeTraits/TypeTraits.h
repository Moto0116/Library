#ifndef LIB_TYPETRAITS_H
#define LIB_TYPETRAITS_H


namespace Lib
{
	namespace TypeTraits
	{
		/**
		 * 定数構造体
		 * @tparam T 定数型
		 * @tparam _val 設定する値
		 */
		template<typename T, T _val>
		struct IntegralConstant
		{
			using Type = IntegralConstant<T, _val>;
			using ValueType = T;

			static const ValueType Value = _val;

			operator ValueType() const
			{
				return (Value);
			}
		};

		using TrueType = IntegralConstant<bool, true>;
		using FalseType = IntegralConstant<bool, false>;

		/*** イテレータチェックメタ構造体実装 */
		struct HasIteratorImpl
		{
			template <typename Type>
			static TrueType Check(typename Type::iterator*);

			template <typename Type>
			static FalseType Check(...);
		};

		/**
		 * イテレータチェックメタ構造体
		 * @tparam Type チェックする型
		 */
		template <typename Type>
		struct HasIterator : public decltype(HasIteratorImpl::Check<Type>(nullptr))
		{
		};

		/*** ポインタチェックメタ構造体実装 */
		struct IsPointerImpl
		{
			template <typename Type>
			static TrueType Check(Type _val);

			template <typename Type>
			static FalseType Check(...);
		};

		/**
		 * ポインタチェックメタ構造体実装 
		 * @tparam Type チェックする型
		 */
		template <typename Type>
		struct IsPointer : public decltype(IsPointerImpl::Check<Type>(nullptr))
		{
		};
	}
}


#endif // !LIB_TYPETRAITS_H
