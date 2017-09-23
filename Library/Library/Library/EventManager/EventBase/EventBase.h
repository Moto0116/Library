/**
 * @file	EventBase.h
 * @brief	イベント基底クラス定義
 * @author	morimoto
 */
#ifndef LIB_EVENTBASE_H
#define LIB_EVENTBASE_H


namespace Lib
{
	/**
	 * イベント基底クラス
	 */
	class EventBase
	{
	public:
		/**
		 * コンストラクタ
		 */
		EventBase();

		/**
		 * デストラクタ
		 */
		virtual ~EventBase() = 0;

	};
}


#endif // !LIB_EVENTBASE_H
