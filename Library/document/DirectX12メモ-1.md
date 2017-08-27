# DirectX12 メモ(1)

## 環境
OS : Windows10 Home x64  
CPU : intel Core i7-6700HQ  
グラフィックボード : NVIDIA GeForce gtx 950m  
DirectX12 sdk version : 10.0.15063.0


## デバイスの作成
最初はデバイスを作成するところから.  
デバッグモードの際はデバッグレイヤの有効化を行い、デバイスを生成します.

``` C++
#ifdef _DEBUG
	ID3D12Debug* pDebugController;
	if (SUCCEEDED(D3D12GetDebugInterface(
		__uuidof(*(pDebugController)),
		reinterpret_cast<void**>(&pDebugController))))
	{
		pDebugController->EnableDebugLayer();
		pDebugController->Release();
	}
#endif // !_DEBUG.

	// DirectX12デバイスの生成.
    ID3D12Device* pDevice;
	if (FAILED(D3D12CreateDevice(
		nullptr,                              // Adapterの設定.
		D3D_FEATURE_LEVEL_11_0,               // 最小機能レベルの設定.
		__uuidof(*(pDevice)),                 // UUIDの設定.
		reinterpret_cast<void**>(&pDevice)))) // 生成されるデバイスのポインタ.
	{
		return false;
	}
```


#### D3D12GetDebugInterface  
第一引数 riid  
デバッグインターフェースのGUIDを指定する.  

第二引数  ppvDebug  
デバッグインターフェースのポインタを指定する.  
第一引数と第二引数のGUID指定とポインタ指定はIID_PPV_ARGSマクロを使用することでひとまとめにできるが今回は使用しない.


#### D3D12CreateDevice  
第一引数  pAdapter  
使用するビデオアダプタへのポインタを設定する.  
ポインタの取得はDXGIFactoryのEnumAdapterで行える.  
今回はnullptrでデフォルトのアダプタを使用するよう指定.  

第二引数  MinimumFeatureLevel  
デバイス生成に成功するための最低機能レベルを指定する.
今回はD3D_FEATURE_LEVEL_11_0を指定.

第三引数  riid  
デバイスインターフェースのGUIDを指定する.

第四引数  ppDevice  
デバイスインターフェースのポインタを指定する.  



## CommandQueue. CommandList. CommandAllocator.
DirectX12より前のバージョンでの描画はDeviceやDeviceContextを通して行ってきました.  
しかし、DirectX12からはCommandListに描画命令を蓄え、そのCommandListをCommandQueueに積み込んでいきます.  
積み込み終わった後に実行を命令することで、CommandQueueはCommandListを一つ一つ消化していきます.  
この仕組みはマルチスレッドにおいて、スレッド間の依存性をなくし描画命令を並列して構築、処理の高速化を図るためのものだそうです.  


## コマンドキュー作成  
```C++
// コマンドキューの生成.
ID3D12CommandQueue* pCommandQueue;
D3D12_COMMAND_QUEUE_DESC CommandQueueDesc;
ZeroMemory(&CommandQueueDesc, sizeof(CommandQueueDesc));
CommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; // GPUタイムアウトの設定などを指定.
CommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; // コマンドリストの種類を指定.
if (FAILED(m_pDevice->CreateCommandQueue(
  &CommandQueueDesc,
  __uuidof(*(pCommandQueue)),
  reinterpret_cast<void**>(&pCommandQueue))))
{
  return false;
}

```




## コマンドリスト・コマンドアロケータ作成  



### D3D12_COMMAND_LIST_TYPE

- D3D12_COMMAND_LIST_TYPE_DIRECT  
描画関係のコマンドを実行するための設定  
描画関係のコマンドのほかにもD3D12_COMMAND_LIST_TYPE_COPYで実行可能なリソースのコピーの他、バンドルを記録させて実行することができるらしい.  

- D3D12_COMMAND_LIST_TYPE_BUNDLE  
バンドルと呼ばれるもので、グラフィックコマンドを事前記録しておくための設定
実行自体はD3D12_COMMAND_LIST_TYPE_DIRECTなどで実行する.  
事前記録数には制限があるそうだが、もちろん通常のコマンドリストを実行するよりはるかに高速.  

- D3D12_COMMAND_LIST_TYPE_COMPUTE  
コンピュートシェーダー用の設定.  

- D3D12_COMMAND_LIST_TYPE_COPY  
リソースコピーを行う設定.  
