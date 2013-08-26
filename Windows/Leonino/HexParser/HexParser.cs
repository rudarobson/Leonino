using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hex
{
	public class HexParser
	{
		private const int DATALENOFFSET = 1;
		private const int DATAOFFSET = 9;
		private const int ADDRESSOFFSET = 3;
		private const int TYPEOFFSET = 7;

		private string FilePath { get; set; }
		private StreamReader File { get; set; }
		private int Endianess { get; set; }
		public int LastAddressOffset = 0;

		public HexParser(string filePath,int endianness = 0)
		{
			FilePath = filePath;
			Endianess = endianness;
		}

		public void StartReading()
		{
			LastAddressOffset = 0;
			if (File == null)
				File = new StreamReader(FilePath);
			else
				File.BaseStream.Seek(0, SeekOrigin.Begin);
		}

		public HexRecord ReadLine()
		{
			HexRecord record = new HexRecord();
			if (File.EndOfStream)
			{
				record.Type = HexRecord.EOF;
				return record;
			}

			string line = File.ReadLine();

			record.Type = RecordType(line);
			string data = null;
			switch(record.Type){
				case HexRecord.DataType:
					data = RecordData(line);

					record.ExtendedAddress = LastAddressOffset;
					record.Address = HexToWord(RecordDataAddress(line));
					record.Length = RecordDataLength(line);
					record.CheckSum = 0;//not used
					record.Data = new byte[record.Length];

					for (int i = 0; i < data.Length; i += 2)//two because it's in Hex characters, 2 character = 1 byte
						record.Data[i / 2] = (byte)((HexToByte(data[i]) << 4) | HexToByte(data[i + 1]));
					break;
				case HexRecord.EOF:
					break;
				case HexRecord.ExtendedSegmentAddress:
					break;
				case HexRecord.ExtendedLinearAddressRecord:
					data = RecordData(line);
					record.Length = RecordDataLength(line);
					record.Data = new byte[record.Length];
					for (int i = 0; i < data.Length; i += 2)//two because it's in Hex characters, 2 character = 1 byte
						record.Data[i / 2] = (byte)((HexToByte(data[i]) << 4) | HexToByte(data[i + 1]));
					record.ExtendedAddress = (record.Data[0] << 8) | record.Data[1];
					LastAddressOffset = record.ExtendedAddress << 16;
					break;
					
			}
			return record;
		}

		private string RecordDataAddress(string block)
		{
			return block.Substring(ADDRESSOFFSET, 4);
		}

		private byte HexToByte(char hex)
		{
			return HexConverter.HexToByte(hex);
		}

		private int HexToWord(string hex)
		{
			return (int)HexConverter.HexToMax4Bytes(hex);
		}

		private int RecordType(string block)
		{
			int type = HexToByte(block[TYPEOFFSET]) * 16 + HexToByte(block[TYPEOFFSET + 1]);
			switch (type)
			{

				case HexRecord.DataType:
					return HexRecord.DataType;
				case HexRecord.EOF:
					return HexRecord.EOF;
				case HexRecord.ExtendedSegmentAddress:
					return HexRecord.ExtendedSegmentAddress;
				case HexRecord.ExtendedLinearAddressRecord:
					return HexRecord.ExtendedLinearAddressRecord;
				default:
					throw new Exception("Record Type Unknown!");
			}
		}

		private int RecordDataLength(string block)
		{
			return HexToByte(block[DATALENOFFSET]) * 16 + HexToByte(block[DATALENOFFSET + 1]);
		}

		private string RecordData(string block)
		{
			int type = RecordType(block);

			if (type == HexRecord.EOF)
				return null;

			int len = RecordDataLength(block);
			string ret = block.Substring(DATAOFFSET, 2 * len);

			return ret;
		}

		public virtual void Dispose()
		{
			File.Close();
			File.Dispose();
		}
	}
}
