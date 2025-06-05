//using Microsoft.DirectX.Direct3D;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Forms;

namespace GameEngine.Classes
{
    public class CustomProperty //: GridItem, INotifyPropertyChanged
    {
        private string sName;
        private object objValue;
        private bool bReadOnly;
        private bool bVisible;

        public event PropertyChangedEventHandler PropertyChanged;        

        public string Name { get => sName; set => sName = value; }
        public object ObjValue
        {
            get
            {
                return objValue;
            }
            set
            {
                objValue = value;
            }
        } 
        public bool ReadOnly
        {
            get
            {
                return bReadOnly;
            }
            set
            {                
                bReadOnly = value;
            }
        }
        //public bool BVisible { get => bVisible; set => bVisible = value; }

        //public override GridItemCollection GridItems => this.GridItems;//throw new NotImplementedException();

        //public override GridItemType GridItemType => this.GridItemType;//throw new NotImplementedException();

        //public override string Label => sName = (string)Value;

        //public override GridItem Parent => this;

        //public override PropertyDescriptor PropertyDescriptor => base.PropertyDescriptor;//throw new NotImplementedException();

        //public override object Value => objValue;

        public CustomProperty(string sName, object value, bool bReadOnly, bool bVisible)
        {
            this.sName = sName;
            this.objValue = value;
            this.ReadOnly = bReadOnly;
            this.bVisible = bVisible;            
        }

        //public override bool Select()
        //{
        //    return true;
        //    //throw new NotImplementedException();
        //}
    }

    public class CustomPropertyDescriptor : PropertyDescriptor
    {
        CustomProperty m_Property;
        public CustomPropertyDescriptor(ref CustomProperty myProperty,
                     Attribute[] attrs) : base(myProperty.Name, attrs)
        {
            m_Property = myProperty;
        }

        public override Type ComponentType => this.GetType();

        public override bool IsReadOnly => false;

        public override Type PropertyType => this.GetType();

        public override bool CanResetValue(object component)
        {
            return false;// throw new NotImplementedException();
        }

        public override object GetValue(object component)
        {
            return "";
        }

        public override void ResetValue(object component)
        {
            
        }

        public override void SetValue(object component, object value)
        {
            
        }

        public override bool ShouldSerializeValue(object component)
        {
            return false;
        }
    }

    public class CustomClass : CollectionBase, ICustomTypeDescriptor
    {
        Attribute[] attrs = new Attribute[0];
        AttributeCollection attributeCollection = new AttributeCollection();

        //public CustomClass
        public void Add(CustomProperty Value)
        {
            base.List.Add(Value);
        }

        public void Remove(string Name)
        {
            foreach (CustomProperty prop in base.List)
            {
                if (prop.Name == Name)
                {
                    base.List.Remove(prop);
                    return;
                }
            }
        }

        public AttributeCollection GetAttributes()
        {
            return attributeCollection;
        }

        public string GetClassName()
        {
            return "ClassName";
        }

        public string GetComponentName()
        {
            return "ComponentName";
        }

        public TypeConverter GetConverter()
        {
            return null;// throw new NotImplementedException();
        }

        public EventDescriptor GetDefaultEvent()
        {
            return null;// throw new NotImplementedException();
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            

            CustomProperty customProperty = new CustomProperty("name", "value", false, true);
            return new CustomPropertyDescriptor(ref customProperty, attrs);
            //throw new NotImplementedException();
        }

        public object GetEditor(Type editorBaseType)
        {
            return this.GetType();
        }

        public EventDescriptorCollection GetEvents()
        {
            throw new NotImplementedException();
        }

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return null;
        }

        public PropertyDescriptorCollection GetProperties()
        {
            throw new NotImplementedException();
        }

        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            PropertyDescriptor[] newProps = new PropertyDescriptor[this.Count];
            for (int i = 0; i < this.Count; i++)
            {
                CustomProperty prop = (CustomProperty)this[i];
                newProps[i] = new CustomPropertyDescriptor(ref prop, attributes);
            }            
            attributeCollection = new AttributeCollection(attributes);
            return new PropertyDescriptorCollection(newProps);
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            
            PropertyDescriptor propDes = GetDefaultProperty();
            return propDes; // throw new NotImplementedException();
        }

        public CustomProperty this[int index]
        {
            get
            {
                return (CustomProperty)base.List[index];
            }
            set
            {
                base.List[index] = (CustomProperty)value;
            }
        }
    }
}
