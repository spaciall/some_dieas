class BaseHandler;
class NetworkHandler
{
    void RegisterHandler(BaseHandler handler);
    void Received(Packet packet)
    {
        // 패킷 핸들 처리를 하고 boost::promise를 통해 기다리고 있는 boost::future의 작업을 함
        handler.handle();
        handler.m_promise.set_promise(true);
    }
};
class BaseHandler
{
    virtual void handle() = 0;
    boost::Promise<…> m_promise;    
};
class PlayerPacketHandler : BaseHandler
{
    boost::Future<…> Attacked()
    {
        // 하나의 패킷 처리는 WorkerThread중 하나에서 처리하게 등록하는 처리 과정이 있음
        Future<…> func([]{
        // 핸들링1
		SendPacket(...);
        …    
        }).then([](){
        // 핸들링1이 끝나고 패킷을 받으면 처리되는 핸들링2 과정
        // 핸들링1과 핸들링2는 각각 다른 WorkerThread에서 처리될 수 있음
        …
        });
        return func;
    }
    boost::Future<…> Moved()
    {
        ….
    }
};

