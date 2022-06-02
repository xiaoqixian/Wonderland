/**********************************************
  > File Name		: Klass.java
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 27 Apr 2022 10:13:15 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

import java.util.Map
import java.util.HashMap;
import java.util.List;

abstract class Klass {
    private String name; //类型名称
    private Map<Objecte, Objecte> klassMap;//存储所有类实例一致的部分

    public final Map<Objecte, Objecte> getKlassMap() {
        return this.klassMap;
    }
}

/**
 * 代表所有类的父类
 */
class Objecte {
    private Klass klass;
    private Map<Objecte, Objecte> objectMap; //存储每个实例不一致的变量，主要为成员变量

    public void setKlass(Klass k) {
        this.klass = k;
    }

    public Klass getKlass() {
        return this.klass;
    }
}


/**
 * 代表一个函数
 */
class FunctionKlass extends Klass {
    private static final Function instance;
    private Function() {}

    static {
        instance = new Function();
    }

    public static Function getInstance() {
        return instance;
    }
}

class FunctionObject extends Objecte {
    private byte[] functionCode; //存储函数的字节码,实际也要用一个类型表示，懒得写了
    private List<Objecte> args; //存储函数的所有参数

    public FunctionObject(byte[] functionCode) {
        this.functionCode = functionCode;
    }

    public FunctionObject(byte[] functionCode, List<Objecte> args) {
        this.functionCode = functionCode;
        this.args = args;
    }
}

class IntegerKlass extends Klass {
    private static final IntegerKlass instance;
    private IntegerKlass() {
        this.name = "Integer";
        this.klassMap = new HashMap<>();
        this.klassMap.put("get", new FunctionObject(...))//这里是添加Integer的一个函数
    }

    static {
        instance = new IntegerKlass();
    }

    public static IntegerKlass getInstance() {
        return instance;
    }
}

class IntegerObject extends Objecte {
    private int value;

    public IntegerObject(int value) {
        this.value = value;
        this.klass = IntegerKlass.getInstance();
    }
}

/**
 * 运行函数，与上面无关
 */
public class Run {
    public static void main(String[] args) {
        Objecte o = new IntegerObject(1);//对于任意实例
        Klass k = o.getKlass();

        //通过Klass获取函数实例
        Map<Objecte, Objecte> map = k.getKlassMap();
        FunctionObject fo = map.get("get");
        fo.invoke(...);
    }
}
