package  
{
	/**
	 * ...
	 * @author Qiaosen Huang
	 */
	public class Packet 
	{
		public static function makeHead(data:String):String {
			var size:String = (data.length).toString(16);
			var head:String = "";
			for (var i:uint = 0; i < 8 - size.length; i++) {
				head += " ";
			}
			head += size;
			return head;
		}
		public static function pack(data:Object):String {
			var result:String = "";
			for (var key:String in data) {
				if (data[key] is String) {
					result += "{0," + key + "," + data[key] + "},";
				} else if (data[key] is int) {
					result += "{1," + key + "," + data[key].toString() + "},";
				} else if (data[key] is Number) {
					result += "{2," + key + "," + data[key].toString() + "},";
				} else if (data[key] is Object) {
					result += "{3," + key + "," + Packet.pack(data[key]) + "},";
				}
			}
			return result;
		}
		public static function unpack(data:String):Object {
			var result:Object = new Object();
			var i:uint = 0;
			while (i < data.length) {
				var count:uint = 0;
				var type:String = data.charAt(i + 1);
				var j:uint = i + 3;
				while (true) {
					if (data.charAt(j) == ",") {
						break;
					}
					j++;
				}
				var name:String = data.substr(i + 3, j - i - 3);
				j++;
				count = j;
				if (type == "3") {
					var bracket_count:uint = 1;
					var array_content:String = "";
					while (true) {
						array_content += data.charAt(j);
						if (data.charAt(j) == "{") {
							bracket_count++;
						} else if (data.charAt(j) == "}") {
							bracket_count--;
						}
						if (bracket_count == 0) {
							break;
						}
						j++;
					}
					array_content=array_content.substr(0, array_content.length - 1);
					result[name] = Packet.unpack(array_content);
					count = j + 2;
				} else {
					while (true) {
						if (data.charAt(j) == ",") {
							break;
						}
						j++;
					}
					var value:String = data.substr(count, j - 1 - count);
					count = j + 1;
					switch (type) {
						case "0":
							result[name] = value;
							break;
						case "1":
							result[name] = parseInt(value, 10);
							break;
						case "2":
							result[name] = parseFloat(value);
							break;
					}
				}
				i = count;
			}
			return result;
		}
	}

}