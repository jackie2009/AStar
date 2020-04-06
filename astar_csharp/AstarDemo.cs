using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;

public class AstarDemo : MonoBehaviour
{
	private string testdataStr =@"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111111110000000100000000000001000000010000000111000100000001011111110100010000000101000000010001000000010100111001000100000001010010001100010000000101001111100001000000010100000000000100000001011111111111110000000100000000000000000000011111111111111100000000000000000000000000000000000000000000000";
	
	private int row = 22;

	private int col = 22;

	private byte[][] mapdata;
	private List<AstarPosVo> rst;

	// Use this for initialization
	void Start ()
	{
 
		print(testdataStr.Length);
 
		mapdata=new byte[row][];
		for (int i = 0; i < row; i++)
		{
			mapdata[i]=new byte[col];
			for (int j = 0; j < col; j++)
			{
				mapdata[i][j] = testdataStr[j + i * col] == '1' ? (byte)1 :(byte) 0;
				var go = GameObject.CreatePrimitive(PrimitiveType.Cube);
				go.transform.position=new Vector3(j,0,i)*1.1f;
				go.GetComponent<Renderer>().material.color=mapdata[i][j]==1? Color.red: Color.green;
			}
		}
	}

	private void OnDrawGizmosSelected()
	{
		if (rst == null) return;
		for (int i = 0; i < rst.Count-1; i++)
		{
			Gizmos.DrawLine(new Vector3(rst[i].x,0.51f,rst[i].y)*1.1f,new Vector3(rst[i+1].x,0.51f,rst[i+1].y)*1.1f );
		}
		 
	}

	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown(0))
		{
			Stopwatch sw=new Stopwatch();
			sw.Start();
			for (int i = 0; i < 100; i++)
			{
				rst=Astar.instance.find(mapdata,row,col,0,19,10,14,30);
			}
			
			  sw.Stop();
			 print( sw.ElapsedMilliseconds);
		}
	}
}
