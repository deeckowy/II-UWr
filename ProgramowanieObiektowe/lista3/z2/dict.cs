using System;

namespace dict
{
    public class Dictionary<Kkey,Vval> where Kkey:IComparable
    {
        private Kkey[] kkeys;
        private Vval[] vvals;
        private int size;
        private int numofelems;
        public Dictionary()
        {
            this.size=1;
            this.kkeys=new Kkey[this.size];
            this.vvals=new Vval[this.size];
            this.numofelems=0;
        }
        public void Add(Kkey key,Vval val)
        {
            if(this.KeyExists(key))throw new Exception("Key already exists");
            this.AddPair(key,val);
            this.numofelems++;
            this.Resize();            
        }
        public Vval Find(Kkey key){return this.GetVval(key);}
        public void Remove(Kkey key)
        {
            if(!this.KeyExists(key))throw new Exception("Key doesn't exist");
            for(int i=this.GetIndex(key);i<this.numofelems-1;i++)
            {
                this.kkeys[i]=this.kkeys[i+1];
                this.vvals[i]=this.vvals[i+1];
            }
            this.numofelems--;
            
        }
        private bool KeyExists(Kkey key)
        {
            for(int i=0;i<this.numofelems;i++)
            {
                if(this.kkeys[i].CompareTo(key)==0)return true;
            }
            return false;
        }
        private void AddPair(Kkey key,Vval val)
        {
            this.kkeys[this.numofelems]=key;
            this.vvals[this.numofelems]=val;
        }
        private void Resize()
        {
            if(this.numofelems==this.size)
            {
                this.size*=2;
                Array.Resize(ref this.kkeys,this.size);
                Array.Resize(ref this.vvals,this.size);
            }
        }
        private Vval GetVval(Kkey key)
        {
            if(!this.KeyExists(key))throw new Exception("Key doesn't exist");
            for(int i=0;i<this.numofelems;i++)
            {
                if(this.kkeys[i].CompareTo(key)==0)return this.vvals[i];
            }
            return default(Vval);
        }
        private int GetIndex(Kkey key)
        {
            for(int i=0;i<this.numofelems;i++)
            {
                if(this.kkeys[i].CompareTo(key)==0)return i;
            }
            return -1;
        }
    }
}