namespace List
{
    public class Item<T>
    {
        private T val;
        private Item<T> next;
        private Item<T> prev;

        public Item(T val)
        {
            this.next=null;
            this.prev=null;
            this.val=val;
        } 

        public T GetVal(){return this.val;}
        public Item<T> GetNext(){return this.next;}
        public Item<T> GetPrev(){return this.prev;}

        public void SetNextItem(Item <T> val){this.next=val;}
        public void SetPrevItem(Item <T> val){this.prev=val;}

        public T RemItem()
        {
            this.next?.SetPrevItem(this.prev);
            this.prev?.SetNextItem(this.next);
            return this.GetVal();
        }

        public bool IsNextNull(){return this.next==null;}
        public bool IsPrevNull(){return this.prev==null;}

    }
}