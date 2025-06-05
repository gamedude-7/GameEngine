using System;

namespace GameEngine
{
    public class ElementPropertyAttribute : Attribute
    {
        public ElementPropertyAttribute(int v)
        {
            V = v;
        }

        public int V { get; }
        public string ListLengthProperty { get; set; }
    }
}