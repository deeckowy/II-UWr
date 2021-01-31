using System;

namespace List
{
    public class List<T>
    {
        private Item<T> start;
        private Item<T> end;
        private int siz;
        public List()
        {
            this.start=null;
            this.end=null;
            this.siz=0;
        }
        public int size(){return this.siz;}
        public bool IsEmpty(){return this.siz==0;}

        public void AddElem(T val)
        {
            Item<T> cp=new Item<T>(val);
            if(this.IsEmpty())
            {
                this.start=cp;
                this.end=this.start;
                this.siz++;
            }
            else
            {
                this.end.SetNextItem(cp);
                cp.SetPrevItem(end);
                this.end=cp;
                this.siz++;
            }
        }

        public T GetFirst()
        {
            if(this.IsEmpty())throw new Exception("List is empty!");
            return this.start.GetVal();
        }
        public T GetLast()
        {
            if(this.IsEmpty())throw new Exception("List is Empty!");
            return this.end.GetVal();
        }
        public T RemLast()
        {
            if(this.IsEmpty())throw new Exception("List is empty!");
            Item<T> cp=this.end;
            if(this.siz==2)
            {
                this.end=this.start;
                this.siz--;
                return cp.RemItem();
            }
            this.siz--;
            this.end=cp.GetPrev();
            return cp.RemItem();
        }
        public T RemFirst()
        {
            if(this.IsEmpty())throw new Exception("List is empty!");
            Item<T> cp=this.start;
            if(this.siz==2)
            {
                this.start=this.end;
                this.siz--;
                return cp.RemItem();
            }
            this.siz--;
            this.start=cp.GetNext();
            return cp.RemItem();
        }
        public void PrintList()
        {
            if(this.IsEmpty())throw new Exception("List is empty!");
            Item<T> cp=this.start;
            for(int i=0;i<this.size();i++)
            {
                Console.WriteLine(cp.GetVal());
                cp=cp.GetNext();
            }
        }
    }
}