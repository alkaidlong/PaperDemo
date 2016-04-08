#pragma once
#include "CorePlatform/CorePlatform.h"
MEDUSA_BEGIN;
namespace StdString
{
	template<typename T>
	struct ConstValues;
	
	template<>
	struct StdString::ConstValues<char>;
	
	template<>
	struct StdString::ConstValues<wchar_t>;
	
}
namespace Socket
{
	class AddressInfo;
	
	class ClientSocket;
	
	class HostInfo;
	
	class ISocket;
	
	class ProtocolInfo;
	
	class ServerSocket;
	
	class ServiceInfo;
	
}
namespace Pattern
{
	template <typename TBase, class TId>
	struct ArrayObjectFactory_NULL_ErrorPolicy;
	
	template <typename TBase, class TId>
	struct ArrayObjectFactory_Exception_ErrorPolicy;
	
	struct Exception;
	
	template<size_t TSize,typename TId,typename FuncSignature>
	class ArrayObjectFactory;
	
	class DefaultRunnable;
	
	template<typename FuncSignature>
	class Delegate;
	
	class DeprecationManager;
	
	template<typename FuncSignature>
	class Event;
	
	template<typename T>
	struct IClone;
	
	template<typename T>
	struct ICopyFrom;
	
	template <typename TId,typename TObject,typename TObjectNewer,typename THashCoder,typename TKeyCompare,typename TObjectCompare>
	class IdObjectPool;
	
	struct IExecutable;
	
	class IInitializable;
	
	class ILoadable;
	
	struct IRunnable;
	
	class ISerializable;
	
	class ISharable;
	
	class ISharableWithName;
	
	struct IUpdatable;
	
	template<typename T>
	class LazyValue;
	
	template <typename TBase, class TId>
	struct ObjectFactory_NULL_ErrorPolicy;
	
	template <typename TBase, class TId>
	struct ObjectFactory_Exception_ErrorPolicy;
	
	template<typename TId,typename FuncSignature>
	class MapObjectFactory;
	
	template<typename T>
	class NullableValue;
	
	template <typename TId,typename TObject,typename THashCoder,typename TKeyCompare>
	class ObjectCache;
	
	template <typename TObject,typename TObjectCompare,typename TObjectNewer>
	class ObjectPool;
	
	struct IOverrideValue;
	
	template<typename T,uint TIndex>
	class OverrideValue;
	
	template<typename T>
	class Singleton;
	
	class StaticConstructor;
	
	template<typename T>
	class SwapValue;
	
	template<typename T>
	class VaryValue;
	
	template<typename TTarget,typename TArg>
	class ArgDelegateAction;
	
	template<typename TTarget>
	class BaseActionRunner;
	
	template<typename TTarget,typename TAnimation>
	class BaseAnimationAction;
	
	template<typename TTarget>
	class BaseFiniteAction;
	
	template<typename TTarget>
	class BaseInfiniteAction;
	
	template<typename TTarget>
	class BaseInstantAction;
	
	template<typename TTarget>
	class DelayAction;
	
	template<typename TTarget>
	class DelegateAction;
	
	template<typename TTarget>
	class IAction;
	
	template<typename TTarget>
	struct IActionRunnable;
	
	template<typename TTarget>
	class BaseMultipleCompositeAction;
	
	template<typename TTarget>
	class BaseSingleCompositeAction;
	
	template<typename TTarget>
	class RepeatedAction;
	
	template<typename TTarget>
	class RepeatedForeverAction;
	
	template<typename TTarget>
	class ReverseAction;
	
	template<typename TTarget>
	class SequenceAction;
	
	template<typename TTarget>
	class SpawnAction;
	
	template<typename TTarget>
	class SpeedAction;
	
	template<typename TTarget>
	class BackEaseInAction;
	
	template<typename TTarget>
	class BackEaseInOutAction;
	
	template<typename TTarget>
	class BackEaseOutAction;
	
	template<typename TTarget>
	class BaseTweenAction;
	
	template<typename TTarget>
	class BezierAction;
	
	template<typename TTarget>
	class BounceEaseInAction;
	
	template<typename TTarget>
	class BounceEaseInOutAction;
	
	template<typename TTarget>
	class BounceEaseOutAction;
	
	template<typename TTarget>
	class CircularEaseInAction;
	
	template<typename TTarget>
	class CircularEaseInOutAction;
	
	template<typename TTarget>
	class CircularEaseOutAction;
	
	template<typename TTarget>
	class CubicEaseInAction;
	
	template<typename TTarget>
	class CubicEaseInOutAction;
	
	template<typename TTarget>
	class CubicEaseOutAction;
	
	template<typename TTarget>
	class ElasticEaseInAction;
	
	template<typename TTarget>
	class ElasticEaseInOutAction;
	
	template<typename TTarget>
	class ElasticEaseOutAction;
	
	template<typename TTarget>
	class ExponentialEaseInAction;
	
	template<typename TTarget>
	class ExponentialEaseInOutAction;
	
	template<typename TTarget>
	class ExponentialEaseOutAction;
	
	template<typename TTarget>
	class QuadraticEaseInAction;
	
	template<typename TTarget>
	class QuadraticEaseInOutAction;
	
	template<typename TTarget>
	class QuadraticEaseOutAction;
	
	template<typename TTarget>
	class QuarticEaseInAction;
	
	template<typename TTarget>
	class QuarticEaseInOutAction;
	
	template<typename TTarget>
	class QuarticEaseOutAction;
	
	template<typename TTarget>
	class QuinticEaseInAction;
	
	template<typename TTarget>
	class QuinticEaseInOutAction;
	
	template<typename TTarget>
	class QuinticEaseOutAction;
	
	template<typename TTarget>
	class RateEaseInAction;
	
	template<typename TTarget>
	class RateEaseInOutAction;
	
	template<typename TTarget>
	class RateEaseOutAction;
	
	template<typename TTarget>
	class SinusoidalEaseInAction;
	
	template<typename TTarget>
	class SinusoidalEaseInOutAction;
	
	template<typename TTarget>
	class SinusoidalEaseOutAction;
	
	class ComponentCache;
	
	class ComponentFactory;
	
	class ComponentList;
	
	class IComponent;
	
	struct IComponentCompare;
	
	class DependencyEffectiveValue;
	
	class DependencyObject;
	
	class DependencyProperty;
	
	class DependencyPropertyMetaData;
	
	template<typename T>
	struct INotifyPropertyChanged;
	
	template<typename T>
	class IProperty;
	
	template<typename TClass,typename T>
	class IPropertyPtr;
	
	class PropertyChangedEventArg;
	
	template<typename T>
	class LazyStrongPtr;
	
	template<typename T>
	class NotNullPtr;
	
	class RTTIClass;
	
	class RTTIObject;
	
}
namespace Math
{
	template<const double& R>
	struct CompileSinHelper;
	
	template<const double& R>
	struct CompileCosHelper;
	
}
namespace Dynamic
{
	template<typename T>
	class Callbacks;
	
}
namespace DeviceType
{
	class Environment;
	
}
namespace Compile
{
	class NullType;
	
	class EmptyType;
	
	template <int v>
	struct Int2Type;
	
	template <bool v>
	struct Bool2Type;
	
	template <typename T>
	struct Type2Type;
	
	template<typename T,T val>
	struct IntegralConstant;
	
	template<bool test,typename T>
	struct If;
	
	template<typename T>
	struct If<true,T>;
	
	template <bool flag, typename T1, typename T2>
	struct IfElse;
	
	template <typename T1, typename T2>
	struct IfElse<false, T1, T2>;
	
	template <typename T1, typename T2>
	struct IsSameType;
	
	template <typename T>
	struct IsSameType<T,T>;
	
	template <class T>
	struct RemoveConst;
	
	template <class T>
	struct RemoveConst<const T>;
	
	template <class T>
	struct RemoveConst<const T[]>;
	
	template <class T,size_t N>
	struct RemoveConst<const T[N]>;
	
	template <class T>
	struct AddConst;
	
	template <class T>
	struct AddConst<T&>;
	
	template <class T>
	struct RemoveVolatile;
	
	template <class T>
	struct RemoveVolatile<volatile T>;
	
	template <class T>
	struct RemoveVolatile<volatile T[]>;
	
	template <class T,size_t N>
	struct RemoveVolatile<volatile T[N]>;
	
	template <class T>
	struct AddVolatile;
	
	template <class T>
	struct RemoveConstVolatile;
	
	template <class T>
	struct AddConstVolatile;
	
	template <class T>
	struct RemoveReference;
	
	template <class T>
	struct RemoveReference<T &>;
	
	template <class T>
	struct RemoveReference<T&&>;
	
	template <class T>
	struct AddReference;
	
	template <typename T>
	struct RemovePointer;
	
	template <typename T>
	struct RemovePointer<T*>;
	
	template <typename T>
	struct RemovePointer<T*const>;
	
	template <typename T>
	struct RemovePointer<T*volatile>;
	
	template <typename T>
	struct RemovePointer<T*const volatile>;
	
	template <typename T>
	struct AddPointer;
	
	template<typename T>
	struct RemoveExtent;
	
	template<typename T,unsigned int N>
	struct RemoveExtent<T[N]>;
	
	template<typename T>
	struct RemoveAllExtents;
	
	template<typename T,unsigned int N>
	struct RemoveAllExtents<T[N]>;
	
	template<typename T>
	struct RemoveAllExtents<T[]>;
	
	template <class U>
	struct AddParameterType;
	
	template <class U>
	struct AddParameterType<U &>;
	
	template <>
	struct AddParameterType<void>;
	
	class TypeInfo;
	
	class MyNil;
	
	template <class THead, class TTail>
	struct Typelist;
	
	template <typename T>
	class TypeTraits;
	
}
class Algorithm;

template<typename T>
struct InnerTypes;

class GuillotineBinPack;

class SkylineBinPack;

struct Skyline;

class CoderFactory;

class FileListFileCoderHashCoder;

class FileListFileCoderComparer;

class CoderPool;

class ICoder;

class LZMADecoder;

class LZMAEncoder;

class XORDecoder;

class XOREncoder;

class XXTEAEncryptor;

template<typename T, size_t TSize,typename TCompare >
class Array;

class ArrayEnumerator;

class ConstArrayEnumerator;

template<size_t TSize>
class BitArray;

template<typename TKey,typename TValue,typename THashCoder,typename TKeyCompare,typename TValueCompare>
class Dictionary;

struct Entry;

class DictionaryEnumerator;

class ConstDictionaryEnumerator;

template<typename T>
class Enumerator;

class HashHelper;

template<typename T,typename THashCoder,typename TCompare>
class HashSet;

class HashSetEnumerator;

class ConstHashSetEnumerator;

template<typename T>
struct ICollection;

template<typename TKey,typename TValue,typename TKeyValuePair,typename TKeyCompare,typename TValueCompare>
struct IDictionary;

template<typename T>
struct IEnumerable;

template<typename T>
struct IEnumerator;

template<typename T>
struct LinkedListNode;

template<typename T >
class ILinkedList;

template<typename T>
class IList;

template<typename T,typename TCompare >
struct ISet;

template<typename T>
class ISortedList;

template<typename TKey,typename TValue>
struct KeyValuePair;

template<typename T,typename TCompare >
class LinkedList;

class LinkListEnumerator;

class ConstLinkListEnumerator;

class Linq;

template<typename T,class TCompare >
class List;

class ListEnumerator;

class ConstListEnumerator;

template<typename T,class TCompare >
class Queue;

class QueueEnumerator;

class ConstQueueEnumerator;

template<typename TKey,typename TValue,typename TKeyCompare >
class SortedDictionary;

template<typename T,typename TCompare, typename TSorter >
class SortedList;

class SortedListEnumerator;

class ConstSortedListEnumerator;

template<typename T,class TCompare >
class Stack;

class StackEnumerator;

class ConstStackEnumerator;

template<typename T>
struct STLMapLessPtr;

template<typename T>
struct STLMapLessPtrForPointer;

template<typename T>
struct DefaultCompare;

template<typename T>
struct CustomCompare;

template<typename T>
struct DefaultCompareForPointer;

template<typename T>
struct CustomCompareForPointer;

template<typename T>
struct InverseCompare;

template<typename T>
struct InverseCustomCompare;

template<typename T>
struct NoCompare;

template<typename T>
struct EqualCompare;

template<typename T>
struct ObjectEqualCompare;

template<typename T>
struct PointerEqualCompare;

template<typename T>
struct DefaultHashCoder;

template<typename T>
struct SafeEnumHashCoder;

template<typename T>
struct DefaultPointerHashCoder;

template<typename T>
struct DefaultDeleter;

template<typename T>
struct NoDeleter;

template<typename TObject>
struct DefaultNewer;

template<typename TId,typename TObject>
struct DefaultNewerById;

class ZipReader;

struct ZipFileInfo;

class ServerConfig;

class ServerList;

class ThreadEventDispatcher;

class UIEventDispatcher;

template<typename TSender,typename TEventArg>
struct WorkItem;

class IEventArg;

template<typename T>
class UserDataEventArg;

class ITrigger;

template<typename T,template<typename T1> class TPoint>
class AABBBox_t;

class Color3F;

class Color3B;

class Color4F;

class Color4B;

template<typename T>
class Cube;

class Quaternion;

class Matrix3;

class EulerAngle;

class GeometryFactory;

template<typename T>
class Line2;

template<typename T>
class Line3;

class Matrix2;

class Matrix4;

class Matrix43;

template<typename T>
class Padding4;

template<typename T>
class Point2;

template<typename T>
class Point3;

template<typename T>
class Point4;

template<typename T>
class Quad;

template<typename T>
class Range;

template<typename T>
class Rect2;

template<typename T>
class Rotation2;

template<typename T>
class Rotation3;

template<typename T>
class Scale2;

template<typename T>
class Scale3;

class ShapeVertex;

template<typename T>
class Size2;

template<typename T>
class Size3;

class TextureVertex;

template<typename T>
class Thickness;

template<typename T,template<typename T1> class TPoint>
class Triangle_t;

class DefaultMoveable;

class TransformMoveable;

class TransformFactory;

class Directory;

class File;

class FileId;

class FileIdStorage;

class FileInfo;

class MemoryFileAutoRegister;

class Path;

class FileCoderList;

class FileList;

class FileListFileItem;

class FileSystem;

class FileSystemNameItem;

class FileSystemOrderItem;

class FileSystemTagItem;

class IFileSystemAccessor;

class AndroidFileSystemAccessor;

class PosixFileSystemAccessor;

class Package;

struct PackageFile;

struct PackageCoderInfo;

struct PackageHeader;

class FileStream;

class IStream;

class MemoryStream;

class ProxyStream;

class FileDownloadingProgressEventArg;

class FileUpdater;

class ServerStatusEventArg;

class CallbackLogger;

class FileLogger;

class ILogger;

class Log;

class AndroidTraceLogger;

class IOSConsoleLogger;

class LinuxConsoleLogger;

class WindowsConsoleLogger;

class WindowsTraceLogger;

class MathStrategy;

class Random;

class IScrollMathModel;

class SpringScrollMathModel;

template<typename T>
class MemoryData;

class BaseCustomMessage;

template<typename TRequest,typename TResponse>
class BaseMessage;

template<typename TRequest,typename TResponse>
class BaseRequestMessage;

class IMessage;

class MessageDispatcher;

class MessageEventArg;

class MessageFactory;

class IMessageHandler;

class MessageHandlerFactory;

class MockMessageHandler;

class TcpMessageHandler;

class GlobalDownloadingProgressEventArg;

class HTTPClient;

class HTTPFileDownloader;

class HTTPMemoryDownloader;

class IHTTPDownloader;

class SingleDownloadingProgressEventArg;

class AutoStopWatch;

class ProfileManager;

class ProfileNode;

class ProfileSample;

class StopWatch;

class ScriptManager;

class ScriptModule;

class ScriptObject;

template<typename T,bool TIsResetKey>
class SecurityValueAutoUnlock;

template<typename T,bool TIsResetKey>
class SecurityValue;

template<typename T>
class BaseString;

template<typename T>
class THeapString;

template<typename T, size_t TBufferSize, bool TIsInitNULL>
class TStackString;

template< size_t TBufferSize, bool TIsInitNULL>
class StackString;

template< size_t TBufferSize, bool TIsInitNULL>
class WStackString;

class StringParser;

template<typename T>
class TStringRef;

class FuckyString;

class FuckyStringNode;

class RandomName;

class StringNameItem;

class StringOrderItem;

class StringTable;

class EnvironmentTag;

class System;

struct MyStreamInfoStruct;

class Lock;

class Mutex;

class ReadWriteLock;

class Semaphore;

class Thread;

class ThreadEvent;

template<typename THost>
class NoThreadingLockPolicy;

template<typename THost>
class ClassThreadingLockPolicy;

template<typename THost>
class ObjectThreadingLockPolicy;

class DateTime;

class Guid;

class MD5;

class TimeSpan;

class Version;

#pragma region typedef
typedef Cube<uint32> CubeI;
typedef Cube<float> CubeF;
typedef CubeF BoundingBox;
typedef Pattern::LazyValue<BoundingBox> LazyBoundingBox;
typedef Line2<int> Line2I;
typedef Line2<float> Line2F;
typedef Line3<int> Line3I;
typedef Line3<float> Line3F;
typedef Pattern::LazyValue<Matrix3> LazyMatrix3;
typedef Pattern::LazyValue<Matrix4> LazyMatrix4;
typedef Pattern::LazyValue<Matrix43> LazyMatrix43;
typedef Padding4<int> Padding4I;
typedef Padding4<float> Padding4F;
typedef Point2<int> Point2I;
typedef Point2<uint> Point2U;
typedef Point2<float> Point2F;
typedef Point2I Vector2I;
typedef Point2F Vector2F;
typedef Point3<int> Point3I;
typedef Point3<float> Point3F;
typedef Point3I Vector3I;
typedef Point3F Vector3F;
typedef Point4<int> Point4I;
typedef Point4<float> Point4F;
typedef Point4I Vector4I;
typedef Point4F Vector4F;
typedef Quad<Color4F> QuadColor;
typedef Quad<Point2<float> > QuadTexCoord;
typedef Quad<Point3<float> > QuadVertex3;
typedef Quad<Point2<float> > QuadVertex2;
typedef Quad<TextureVertex> QuadTextureVertex;
typedef Quad<ShapeVertex> QuadShapeVertex;
typedef Range<int> RangeI;
typedef Range<uint32> RangeU;
typedef Range<float> RangeF;
typedef Rect2<int> Rect2I;
typedef Rect2<uint> Rect2U;
typedef Rect2<float> Rect2F;
typedef Rotation2<float> Rotation2F;
typedef Rotation3<float> Rotation3F;
typedef Scale2<float> Scale2F;
typedef Scale3<int> Scale3I;
typedef Scale3<float> Scale3F;
typedef Size2<int> Size2I;
typedef Size2<uint32> Size2U;
typedef Size2<float> Size2F;
typedef Size3<uint32> Size3U;
typedef Size3<int> Size3I;
typedef Size3<float> Size3F;
typedef Thickness<float> ThicknessF;
typedef Triangle_t<int,Point2> Triangle2I;
typedef Triangle_t<float,Point2> Triangle2F;
typedef Triangle_t<int,Point3> Triangle3I;
typedef Triangle_t<float,Point3> Triangle3F;
typedef Triangle3I Triangle;
typedef Triangle3F TriangleF;
typedef MemoryData<short> MemoryShortData;
typedef MemoryData<byte> MemoryByteData;
typedef MemoryData<char> MemoryCharData;
typedef MemoryData<wchar_t> MemoryWCharData;
typedef MemoryData<int> MemoryIntData;
typedef MemoryData<uint> MemoryUIntData;
typedef Pattern::Delegate<void()> Action0;
typedef SecurityValue<int,false> SecurityInt;
typedef SecurityValue<int,true> StrongSecurityInt;
typedef THeapString<char> HeapString;
typedef THeapString<wchar_t> WHeapString;
typedef TStringRef<char> StringRef;
typedef TStringRef<wchar_t> WStringRef;
#pragma endregion typedef
MEDUSA_END;
