package 
{
	import flash.display.InteractiveObject;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.ProgressEvent;
	import flash.net.Socket;
	
	/**
	 * ...
	 * @author Qiaosen Huang
	 */
	public class Main extends Sprite 
	{
		
		public function Main():void 
		{
			var s:Socket = new Socket();
			var args:Object = new Object();
			args["cmd"] = 0 as int;
			args["message"] = "hellow world";
			var msg:String = Packet.pack(args);
			trace(msg.length)
			s.addEventListener(Event.CONNECT, function(e:Event) {
				
			s.writeUTFBytes(Packet.makeHead(msg));
			s.writeUTFBytes(msg);
			s.flush();
			});
			s.addEventListener(ProgressEvent.SOCKET_DATA, headHandler);
			s.connect("68.62.87.97", 48011);
		}
		private function headHandler(e:ProgressEvent):void {
			var s:Socket = e.target as Socket;
			var rawData:String = s.readUTFBytes(8);
			rawData = rawData.replace(" ", "");
			var head_length:int = parseInt(rawData, 16);
			s.removeEventListener(ProgressEvent.SOCKET_DATA, headHandler);
			s.addEventListener(ProgressEvent.SOCKET_DATA, dataHandler(head_length));
		}
		private function dataHandler(head_length:int):Function {
			return function(e:ProgressEvent):void {
				var s:Socket = e.target as Socket;
				var rawData:String = s.readUTFBytes(head_length);
				trace(rawData);
				trace(parseObject(Packet.unpack(rawData)));
				s.removeEventListener(ProgressEvent.SOCKET_DATA, dataHandler(head_length));
				s.addEventListener(ProgressEvent.SOCKET_DATA, headHandler);
			}
		}
		private function parseObject(a:Object):String {
			if (a is String || a is int || a is Number) {
				return a.toString();
			}
			var result:String = "";
			for (var key:String in a) {
				result+="["+key+":"+parseObject(a[key])+"],"
			}
			return result;
		}
		
	}
	
}