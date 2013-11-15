class Packet(object):
	header_length=8
	@staticmethod
	def unpack(p):
		result={}
		i=0
		while(i<len(p)):
			count=0
			typeid=int(p[i+1])
			#retrieve name
			name_start=i+3
			j=i+3
			while(1):
				if p[j]==",":
					break
				j+=1
			name=p[name_start:j]
			count=j+1
			j=count
			if typeid==3:
				bracket_count=1
				array_content=""
				while(1):
					array_content+=p[j]
					if p[j]=="{":
						bracket_count+=1
					elif p[j]=="}":
						bracket_count-=1
					if bracket_count==0:
						break
					j+=1
				array_content=array_content[:-1]
				result[name]=Packet.unpack(array_content)
				count=j+2
			else:
				#retrieve value
				while(1):
					if p[j]==",":
						break
					j+=1
				value=p[count:j-1]
				count=j+1

				if typeid==1:
					result[name]=int(value)
				elif typeid==2:
					result[name]=float(value)	
				else:	
					result[name]=value
			i=count
		return result

	@staticmethod
	def pack(d):
		result=""
		if type(d)!=dict:
			return ""
		for k,v in d.iteritems():
			typename=type(v)
			if typename==str:
				result+=("{0,%s,%s},"%(k,v))
			elif typename==int:
				result+=("{1,%s,%i},"%(k,v))
			elif typename==float:
				result+=("{2,%s,%f},"%(k,v))
			elif typename==dict:
				result+="{3,%s,%s},"%(k,self.pack(v))
		return result













