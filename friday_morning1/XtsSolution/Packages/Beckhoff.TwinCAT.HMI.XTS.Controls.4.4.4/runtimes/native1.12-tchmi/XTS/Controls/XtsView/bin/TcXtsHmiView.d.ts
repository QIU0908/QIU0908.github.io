declare module TcHmi.Common.BaseTypes {
    type Unit = "px" | "%";
    interface Padding {
        leftUnit: Unit;
        topUnit: Unit;
        rightUnit: Unit;
        bottomUnit: Unit;
        left: number;
        top: number;
        right: number;
        bottom: number;
    }
}
declare module TcHmi.Common.BaseTypes {
    interface Position2D {
        x: number;
        y: number;
    }
}
declare module TcHmi.Common.BaseTypes {
    class Matrix {
        protected values: number[][];
        constructor(row: number, column: number);
        static GenerateFromPoint(point: Point): Matrix;
        static FromM3(m3: M3): Matrix;
        GenerateToPoint(): Point;
        Multiply(matrix: Matrix): Matrix;
        Identity(): void;
        Get(row: number, column: number): number;
    }
}
declare module TcHmi.Common.BaseTypes {
    class M3 extends Matrix {
        static FromValues(values: number[][]): M3;
        private m12;
        private m13;
        private m21;
        private m22;
        private m11;
        private m23;
        private m31;
        private m32;
        private m33;
        constructor();
        get M12(): number;
        get M13(): number;
        get M21(): number;
        get M22(): number;
        get M11(): number;
        get M23(): number;
        get M31(): number;
        get M32(): number;
        get M33(): number;
        get Values(): number[][];
        static get Identity(): M3;
        GetInverse(): M3;
        GetSubdertimnant(row: number, column: number): number;
        Det(): number;
        GenerateMatrix(): void;
        Scale(sx: number, sy: number): void;
        Multiply(m3: M3): M3;
        Translate(tx: number, ty: number): void;
        RotateRad(angle: number): void;
        Rotate(angle: number): void;
    }
}
declare module TcHmi.Common.BaseTypes {
    class Rect {
        height: number;
        width: number;
        topLeft: Point;
        constructor(height?: number, width?: number, topLeft?: Point);
        Union(rect: Rect): Rect;
        ContainsPoint(point: Point): boolean;
    }
}
declare module TcHmi.Common.BaseTypes {
    class Point {
        static FromPosition(position: Position2D): Point;
        X: number;
        Y: number;
        constructor(x?: number, y?: number);
        Set(x: number, y: number): void;
        Add(point: Point): void;
        Sub(point: Point): Point;
        Transform(m3: M3): Point;
        Length(): number;
        static GetArea(a: Point, b: Point, c: Point): number;
    }
}
declare module TcHmi.Common.BaseTypes {
    class TextConfiguration {
        Text: string;
        Color: TcHmi.SolidColor;
        FontStyle: TcHmi.FontStyle;
        FontWeight: TcHmi.FontWeight;
        FontFamily: TcHmi.FontFamily;
        HorizontalAlignment: TcHmi.HorizontalAlignment;
        VerticalAlignment: TcHmi.VerticalAlignment;
        FontSize: number;
        constructor(init?: Partial<TextConfiguration>);
        GetCanvasTextAlign(): CanvasTextAlign;
        GetCanvasTextBaseline(): CanvasTextBaseline;
        GetCanvasTextFont(): string;
    }
}
declare module TcHmi.Common.Utilities {
    abstract class ColorConverter {
        private static ComponentToHex;
        static RgbToHex(r: number, g: number, b: number): string;
        static HexToRgb(hex: string): string | null;
        static FromArgb(hex: number): string;
    }
}
declare module TcHmi.Common.Utilities {
    abstract class ImageHandler {
        private static images;
        static GetImage(src: string): HTMLImageElement;
        static BinaryToDataUrl(input: any): string;
    }
}
declare module TcHmi.Common.Utilities {
    abstract class BitUtil {
        static IsBitSet(value: number, index: number): boolean;
    }
}
declare module TcHmi.Common.Scenegraph {
    interface IRenderable {
        readonly ZIndex: number;
        Render(ctx: CanvasRenderingContext2D): void;
        GetBounds(): BaseTypes.Rect;
    }
}
declare module TcHmi.Common.Scenegraph {
    interface ITransformable {
        readonly Transformation: BaseTypes.M3;
        IsVisible: boolean;
        AddChild(transformable: ITransformable): void;
        TransformNode(m3: BaseTypes.M3): void;
        ClearChilds(): void;
        SetTransformation(m3: BaseTypes.M3, parentWorldMatrix: BaseTypes.M3): void;
        RemoveChild(transformable: ITransformable): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    interface IRenderableCollection {
        AddRenderable(renderable: IRenderable): void;
        RemoveRenderable(renderable: IRenderable): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    interface ISelectionManager {
        Click(point: TcHmi.Common.BaseTypes.Point): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    class TransformableBase<T extends ITransformable = ITransformable> implements ITransformable {
        private isVisible;
        protected transformChilds: T[];
        protected matrix: BaseTypes.M3;
        protected worldMatrix: BaseTypes.M3;
        get Childs(): T[];
        get IsVisible(): boolean;
        set IsVisible(isVisible: boolean);
        get Transformation(): BaseTypes.M3;
        AddChild<Transformable extends T>(transformable: Transformable): Transformable;
        TransformNode(m3: BaseTypes.M3): void;
        ClearChilds(): void;
        SetTransformation(m3: BaseTypes.M3, parentWorldMatrix: BaseTypes.M3): void;
        RemoveChild(transformable: T): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    class RenderableBase extends TransformableBase implements IRenderable {
        private zIndex;
        constructor(zIndex?: number);
        get ZIndex(): number;
        protected TransformCanvas(ctx: CanvasRenderingContext2D, m3: BaseTypes.M3): void;
        Render(ctx: CanvasRenderingContext2D): void;
        GetBounds(): BaseTypes.Rect;
    }
}
declare module TcHmi.Common.Scenegraph {
    class RenderableGroup<T extends IRenderable> implements IRenderable, IRenderableCollection {
        private zIndex;
        private childs;
        constructor(zIndex?: number);
        get ZIndex(): number;
        get Childs(): T[];
        get Length(): number;
        ClearChilds(): void;
        Render(ctx: CanvasRenderingContext2D): void;
        RemoveRenderable(renderable: T): void;
        AddRenderable(renderable: T): void;
        private binarySearch;
        GetBounds(): BaseTypes.Rect;
    }
}
declare module TcHmi.Common.Scenegraph {
    class TextNode extends RenderableBase {
        protected canv: HTMLCanvasElement;
        textConfiguration: BaseTypes.TextConfiguration;
        Model: any;
        constructor(textConfiguration: BaseTypes.TextConfiguration, zIndex?: number);
        Render(ctx: CanvasRenderingContext2D): void;
        GetBounds(): BaseTypes.Rect;
    }
}
declare module TcHmi.Common.Scenegraph {
    class VisualGroup<T extends RenderableBase = RenderableBase> extends TransformableBase<T> {
        protected renderableCollection: IRenderableCollection;
        constructor(renderableCollection: IRenderableCollection);
        get Length(): number;
        AddChild<Renderable extends T>(renderable: Renderable): Renderable;
        RemoveChild(renderable: T): void;
        ClearChilds(): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    class ImageNode extends RenderableBase {
        protected img: HTMLImageElement;
        private offsetX;
        private offsetY;
        private renderHeight;
        private renderWidth;
        private horizontalAlignment;
        private verticalAlignment;
        constructor(img: HTMLImageElement, zIndex?: number);
        set RenderHeight(height: number | null | undefined);
        set RenderWidth(width: number | null | undefined);
        set HorizontalAlignment(horizontalAlignment: HorizontalAlignment);
        set VerticalAlignment(verticalAlignment: VerticalAlignment);
        protected drawImage(ctx: CanvasRenderingContext2D): void;
        Render(ctx: CanvasRenderingContext2D): void;
        Loaded(callback: () => void): void;
        private SetWidthParameters;
        private SetHeightParameters;
    }
}
declare module TcHmi.Common.Scenegraph {
    class XSystemRenderer implements IRenderableCollection {
        static readonly MoverZIndex = 10000;
        static readonly MoverCanvZIndexStart = 5000;
        static readonly MoverCanvZIndexEnd = 15000;
        static readonly ModuleZIndex = 0;
        System: ITransformable;
        private visuals;
        private visualsGroupUnderMoverCanv;
        private visualsGroupOnMoverCanv;
        private visualsGroupOverMoverCanv;
        private div;
        private moverCanvas;
        private moverCtx;
        private visualCanvasOverMover;
        private visualCtxOverMover;
        private visualCanvasUnderMover;
        private visualCtxUnderMover;
        private padding;
        private isCanvasAvailable;
        private clientWidth;
        private clientHeigth;
        constructor(div: HTMLElement);
        get CanvasOverMover(): HTMLCanvasElement;
        get CanvasUnderMover(): HTMLCanvasElement;
        get MoverCanvas(): HTMLCanvasElement;
        get IsCanvasAvailable(): boolean;
        get Padding(): BaseTypes.Padding;
        set Padding(padding: BaseTypes.Padding);
        AddRenderable(renderable: IRenderable): void;
        RemoveRenderable(renderable: IRenderable): void;
        AddEventListener(type: string, callback: (this: HTMLElement, ev: any) => any): void;
        private ClearVisualCanvas;
        private ClearMoverCanvas;
        CreateCanvas(width: number, height: number): void;
        RenderAll(): void;
        RenderVisuals(): void;
        RenderMover(): void;
        Resize(width: number, height: number): void;
        TransformView(m3: BaseTypes.M3): void;
        ZoomToFit(): void;
    }
}
declare module TcHmi.Common.Scenegraph {
    class VisualInteractionHandler {
        private lastTouches;
        private lastMiddlePoint;
        private pressing;
        private moved;
        private systemRenderer;
        private selectionManager;
        LockZoom: boolean;
        LockPan: boolean;
        constructor(systemRenderer: XSystemRenderer, selectionManager?: ISelectionManager);
        private InitEventListener;
        private MouseDown;
        private MouseUp;
        private MouseLeave;
        private MouseMove;
        private MouseWheel;
        private Touchend;
        private Touchmove;
    }
}
declare module TcHmi.XTS.BaseTypes {
    enum ModuleType {
        Unknown = 0,
        __START_OF_AT__ = 1,
        AT2000_0250 = 2,
        AT2001_0250 = 3,
        AT2050_0500 = 4,
        AT2050_0501 = 5,
        AT2020_0250 = 6,
        AT2025_0250 = 7,
        AT2040_0250 = 8,
        AT2021_0250 = 9,
        AT2026_0250 = 10,
        AT2041_0250 = 11,
        AT2000_0233 = 12,
        AT2002_0249 = 13,
        AT2002_0250 = 14,
        AT2042_0250 = 15,
        AT2100_0250 = 16,
        AT2102_0250 = 17,
        AT2000_0249 = 18,
        AT2140_0250 = 19,
        __END_OF_AT__ = 20,
        __START_OF_ATH__ = 256,
        ATH2000_0250 = 257,
        ATH2050_0500 = 258,
        ATH2050_0501 = 259,
        __END_OF_ATH__ = 260,
        __START_OF_ECO__ = 514,
        AT2200_0500 = 515,
        AT2202_0500 = 516,
        __END_OF_ECO__ = 517
    }
}
declare module TcHmi.XTS.BaseTypes {
    enum RailSystem {
        Normal = 0,
        Blackline = 1
    }
}
declare module TcHmi.XTS.BaseTypes {
    enum PathType {
        Straight = 0,
        Circular = 1,
        Free = 2
    }
}
declare module TcHmi.XTS.BaseTypes {
    enum MoverType {
        UserSpecific = 0,
        AT9011_0050 = 1,
        AT9011_0070 = 2,
        AT9012_0050 = 3,
        AT9014_0055 = 4,
        AT9014_0070 = 5,
        ATH9011_0075 = 256,
        Hepco = 999
    }
}
declare module TcHmi.XTS.BaseTypes {
    enum ModuleSide {
        Driver = 0,
        Encoder = 1
    }
    class ModuleSideUtil {
        static Invert(moduleSide: ModuleSide): ModuleSide;
    }
}
declare module TcHmi.XTS.Server {
    module ServerTypes {
        interface XtsModel {
            InfoServer: InfoServerModel | null;
            ProcessingUnits: ProcessingUnitModel[];
        }
        interface InfoServerModel {
            Stations: StationModel[];
        }
        interface StationModel {
            Parts: number[];
            Description: string;
            EndPositionOnPart: number;
            IsEnabled: boolean;
            StationColor: number;
            StationId: number;
            StartPositionOnPart: number;
            StopPositions: number[] | undefined;
        }
        interface ProcessingUnitModel {
            MoverType: number;
            Movers: MoverModel[];
            Parts: PartModel[];
            Tracks: TrackModel[];
        }
        interface MoverModel {
            Name: string;
            ObjectId: number;
            Id: string;
        }
        interface MoverPosition {
            PartPosition: number;
            PartOid: number;
        }
        interface TrackModel {
            ObjectId: number;
            PartIds: number[];
        }
        interface PartModel {
            Name: string;
            ObjectId: number;
            Modules: ModuleModel[];
            ModuleSide: number;
        }
        interface PartTransformation {
            OffsetX: number;
            OffsetY: number;
            Rotation: number;
        }
        interface ModuleModel {
            Name: string;
            ObjectId: number;
            ModuleType: number;
            Gap: number;
        }
    }
}
declare module TcHmi.XTS.Server {
    class ServerConnection {
        private targetName;
        private xtsModel;
        private moverPositions;
        private partTransformations;
        private moverIds;
        private moduleDriveStates;
        private moverPosSubscriptionId;
        private moduleDriveStatesSubId;
        private partTransformationSubscriptionId;
        private refreshRate;
        private moverPositionChanged;
        private moduleDriveStateChanged;
        private partTransformationChanged;
        constructor(targetName?: string, refreshRate?: number);
        get XtsModel(): ServerTypes.XtsModel;
        get TargetName(): string;
        get MoverPositions(): ServerTypes.MoverPosition[][];
        get PartTransformations(): ServerTypes.PartTransformation[][];
        get MoverIds(): string[];
        get RefreshRate(): number;
        OnPartTransformationChanged(eventCallback: (transformations: ServerTypes.PartTransformation[][]) => void): DestroyFunction;
        OnMoverPositionChanged(eventCallback: (moverPositionInfos: ServerTypes.MoverPosition[][]) => void): DestroyFunction;
        OnModuleDriveStatesChanged(eventCallback: (moverPositionInfos: number[][]) => void): DestroyFunction;
        set RefreshRate(refreshRate: number);
        UpdateModel(callback?: (model: ServerTypes.XtsModel, command: any) => void): void;
        SetMoverPositionSubscription(): void;
        UnsubscribeMoverPosition(): void;
        SetModuleDriveStateSubscription(): void;
        UnsubscribeModuleDriveStates(): void;
        SetPartTransformationSubscription(): void;
        UnsubscribePartTransformation(): void;
        private RequestErrorHandler;
    }
}
declare module TcHmi.XTS.Controls {
    module ClientTypes {
        class Values {
            static ToolType: {
                readonly Image: "Image";
                readonly Text: "Text";
            };
            static PartSide: {
                readonly Default: "Default";
                readonly Front: "Front";
                readonly Back: "Back";
            };
            static ModuleSide: {
                readonly Front: "Front";
                readonly Back: "Back";
            };
            static MoverIdentificationMode: {
                readonly MoverId: "MoverId";
                readonly MoverIndex: "MoverIndex";
                readonly All: "All";
            };
            static MoverTextOptions: {
                readonly Custom: "Custom";
                readonly MoverID: "MoverId";
                readonly MoverIndex: "MoverIndex";
                readonly MoverPosition: "MoverPosition";
            };
            static SelectionMode: {
                readonly Off: "Off";
                readonly SingleSelection: "SingleSelection";
                readonly MultiSelection: "MultiSelection";
            };
            static XtsLayout: {
                readonly SystemView: "SystemView";
                readonly InvertedSystemView: "InvertedSystemView";
                readonly Custom: "Custom";
            };
            static MarkerType: {
                readonly None: "None";
                readonly Diamond: "Diamond";
                readonly Tick: "Tick";
            };
            static StationText: {
                readonly None: "None";
                readonly StationDescription: "StationDescription";
                readonly StationId: "StationId";
            };
            static MarkerText: {
                readonly None: "None";
                readonly StationDescription: "StopPosition";
            };
            static MoverType: {
                readonly SystemView: "SystemView";
                readonly Custom: "Custom";
            };
        }
        type ToolType = (typeof Values.ToolType)[keyof typeof Values.ToolType];
        type PartSide = (typeof Values.PartSide)[keyof typeof Values.PartSide];
        type ModuleSide = (typeof Values.ModuleSide)[keyof typeof Values.ModuleSide];
        type MoverIdentificationMode = (typeof Values.MoverIdentificationMode)[keyof typeof Values.MoverIdentificationMode];
        type MoverTextOptions = (typeof Values.MoverTextOptions)[keyof typeof Values.MoverTextOptions];
        type SelectionMode = (typeof Values.SelectionMode)[keyof typeof Values.SelectionMode];
        type XtsLayout = (typeof Values.XtsLayout)[keyof typeof Values.XtsLayout];
        type MarkerType = (typeof Values.MarkerType)[keyof typeof Values.MarkerType];
        type StationText = (typeof Values.StationText)[keyof typeof Values.StationText];
        type MarkerText = (typeof Values.MarkerText)[keyof typeof Values.MarkerText];
        type MoverType = (typeof Values.MoverType)[keyof typeof Values.MoverType];
        interface XtsInfoImage {
            ImageSrc: any;
            View: string;
            PositionX: number;
            PositionY: number;
            Width: number | undefined;
            Height: number | undefined;
            Rotation: number | undefined;
            Visible: boolean;
            zIndex: number;
        }
        interface XtsTool {
            ToolType: ToolType;
            MoverSide: ModuleSide;
            ProcessingUnitIndex: number;
            IdentificationId: string;
            IdentificationMode: MoverIdentificationMode;
            zIndex: number;
            OffsetX: number;
            OffsetY: number;
            Rotation: number;
            Visible: boolean;
            ImageSrc: string;
            ImageWidth: number | undefined;
            ImageHeight: number | undefined;
            TextType: MoverTextOptions;
            CustomText: string;
            TextOptions: TextOptions;
        }
        interface TextOptions {
            Color: TcHmi.SolidColor;
            FontStyle: TcHmi.FontStyle;
            FontWeight: TcHmi.FontWeight;
            FontFamily: TcHmi.FontFamily;
            VerticalAlignment: TcHmi.VerticalAlignment;
            HorizontalAlignment: TcHmi.HorizontalAlignment;
            FontSize: number;
        }
        interface PartTransformation {
            ProcessingUnitIndex: number;
            PartIndex: number;
            OffsetX: number;
            ValueScaleX: number;
            AxisBindingX: number | undefined;
            OffsetY: number;
            ValueScaleY: number;
            AxisBindingY: number | undefined;
            Rotation: number;
            PartSide: PartSide;
            Visible: boolean | undefined;
        }
        interface XtsMover {
            ProcessingUnitIndex: number;
            MoverIndex: number;
        }
        interface XtsModule {
            ProcessingUnitIndex: number;
            PartIndex: number;
            ModuleIndex: number;
        }
        interface StationOptions {
            Thickness: number;
            Text: StationText;
            TextInfoBarPlacement: TcHmi.HorizontalAlignment;
            TextDisplacement: number;
            TextOptions: TextOptions;
            zIndex: number;
        }
        interface InfoBarOptions {
            SpaceBetweenInfoBars: number;
            DisplacementToFirst: number;
        }
        interface MarkerOptions {
            MarkerType: MarkerType;
            Size: number;
            Thickness: number;
            Text: MarkerText;
            TextDisplacement: number;
            TextOptions: TextOptions;
            zIndex: number;
        }
        interface DimensionOptions {
            Displacement: number;
            InfoBarThickness: number;
            MarkerThickness: number;
            MarkerSize: number;
            MarkerType: MarkerType;
            TextPattern: number;
            TextDisplacement: number;
            InfoBarColor: TcHmi.SolidColor;
            MarkerColor: TcHmi.SolidColor;
            TextOptions: TextOptions;
            zIndex: number;
        }
        interface XtsInfoBarMarker {
            InfoBarPosition: number;
            MarkerType: MarkerType;
            MarkerThickness: number;
            MarkerSize: number;
            MarkerColor: TcHmi.SolidColor;
            MarkerText: string | null;
            TextDisplacement: number;
            TextOptions: TextOptions;
            zIndex: number;
        }
        interface XtsInfoBar {
            ProcessingUnitIndex: number;
            PartIndex: number;
            PartStartPosition: number;
            PartEndPosition: number;
            InfoBarThickness: number;
            InfoBarDisplacement: number;
            InfoBarColor: TcHmi.SolidColor;
            Visible: boolean;
            InfoBarText: string | null;
            TextPlacement: TcHmi.HorizontalAlignment;
            TextDisplacement: number;
            TextOptions: TextOptions;
            Marker: XtsInfoBarMarker[];
            zIndex: number;
        }
        interface CustomMoverLayout {
            ImageSrcFrontSide: string | null;
            ImageWidthFrontSide: number;
            ImageHeightFrontSide: number;
            XOffsetFrontSide: number;
            YOffsetFrontSide: number;
            ImageSrcBackSide: string | null;
            ImageWidthBackSide: number;
            ImageHeightBackSide: number;
            XOffsetBackSide: number;
            YOffsetBackSide: number;
        }
    }
}
declare module TcHmi.XTS.Controls {
    class ModuleMetaData {
        private static allModules;
        private static pointCloud500;
        private static pointCloud501;
        private static pointCloud500N;
        private static pointCloud501N;
        private static pixelRealityScale;
        static get PixelRealityScale(): number;
        private img;
        private side;
        private railsystem;
        private moduleType;
        private moduleLength;
        private startAngle;
        private startPoint;
        private endAngle;
        private endPoint;
        private width;
        private height;
        private pathType;
        private xScaling;
        private yScaling;
        private pointCloud;
        get Img(): HTMLImageElement;
        get Side(): TcHmi.XTS.BaseTypes.ModuleSide;
        get Railsystem(): TcHmi.XTS.BaseTypes.RailSystem;
        get ModuleType(): TcHmi.XTS.BaseTypes.ModuleType;
        get ModuleLength(): number;
        get StartAngle(): number;
        get StartPoint(): TcHmi.Common.BaseTypes.Point;
        get EndAngle(): number;
        get EndPoint(): TcHmi.Common.BaseTypes.Point;
        get Width(): number;
        get Height(): number;
        get PathType(): TcHmi.XTS.BaseTypes.PathType;
        get XScaling(): number;
        get YScaling(): number;
        get PointCloud(): TcHmi.Common.BaseTypes.Point[];
        static GetMetaDataByModuleType(moduleType: TcHmi.XTS.BaseTypes.ModuleType, side?: TcHmi.XTS.BaseTypes.ModuleSide, railsystem?: TcHmi.XTS.BaseTypes.RailSystem): ModuleMetaData;
        static Initialize(controlBasePath: string): void;
        private static InitPointClouds;
        static InitializeMetaData(controlBasePath: string): void;
    }
}
declare module TcHmi.XTS.Controls {
    class PointCloud {
        static AT2050_0500_Points: number[];
        static AT2050_0501_Points: number[];
    }
}
declare module TcHmi.XTS.Controls {
    class Utilities {
        static TextConfigurationFromTextOptions(textOptions: ClientTypes.TextOptions, text?: string, pixelRealityScale?: number): Common.BaseTypes.TextConfiguration;
    }
}
declare module TcHmi.XTS.Controls {
    class XtsMoverVisual extends TcHmi.Common.Scenegraph.ImageNode {
        Shade: boolean;
        ShadeStyle: string;
        ActualPart: XtsPartVisual;
        private position;
        private drawPositionNode;
        private metaData;
        private indexInXpu;
        private processingUnitIndex;
        private id;
        readonly ToolsGroup: TcHmi.Common.Scenegraph.VisualGroup;
        constructor(metaData: MoverMetaData, xpuIndex: number, moverIndex: number, id: string, toolsRenderer: TcHmi.Common.Scenegraph.IRenderableCollection);
        get IndexInXpu(): number;
        get ProcessingUnitIndex(): number;
        get Id(): string;
        get MetaData(): MoverMetaData;
        protected drawImage(ctx: CanvasRenderingContext2D): void;
        GetBounds(): Common.BaseTypes.Rect;
        SetPosition(position: number): void;
        ClearTools(): void;
        RemoveTool(tool: Common.Scenegraph.RenderableBase): void;
        AddTool(tool: Common.Scenegraph.RenderableBase): void;
        SetTool(tool: ClientTypes.XtsTool): void;
        HitTest(point: TcHmi.Common.BaseTypes.Point): boolean;
    }
}
declare module TcHmi.XTS.Controls {
    class MoverMetaData {
        private static userSpecific_BackSide;
        private static userSpecific_FrontSide;
        img: any;
        movertype: TcHmi.XTS.BaseTypes.MoverType;
        width: number;
        height: number;
        centerMagnetPlate: TcHmi.Common.BaseTypes.Point;
        side: TcHmi.XTS.BaseTypes.ModuleSide;
        static AllMover: MoverMetaData[];
        constructor();
        static GetMetaDataById(type: TcHmi.XTS.BaseTypes.MoverType, side?: TcHmi.XTS.BaseTypes.ModuleSide): MoverMetaData;
        static Initialize(controlBasePath: string): void;
    }
}
declare module TcHmi.XTS.Controls {
    class XtsModuleVisual extends TcHmi.Common.Scenegraph.ImageNode {
        Shade: boolean;
        ShadeStyle: string;
        private metaData;
        private gap;
        private trackLength;
        private indexInPart;
        private partViusal;
        private startPositionInPart;
        readonly VisualChilds: TcHmi.Common.Scenegraph.VisualGroup;
        constructor(metaData: ModuleMetaData, indexInPart: number, partVisual: XtsPartVisual, startPositionInPart: number, gap: number);
        get IndexInPart(): number;
        get MetaData(): ModuleMetaData;
        get PartViusal(): XtsPartVisual;
        get StartPositionInPart(): number;
        get Gap(): number;
        get TrackLength(): number;
        CalculateMoverTransform(localPosition: number): TcHmi.Common.BaseTypes.M3;
        GenerateDisplacementPoints(start: number, end: number, displacement: number): TcHmi.Common.BaseTypes.Point[];
        CalculateDisplacementPointOnCircularPath(position: number, displacement: number): TcHmi.Common.BaseTypes.Point;
        CalculateDisplacementPointOnFreePath(position: number, displacement: number): TcHmi.Common.BaseTypes.Point;
        CalculateEndTransform(): TcHmi.Common.BaseTypes.M3;
        GetBounds(): Common.BaseTypes.Rect;
        protected drawImage(ctx: CanvasRenderingContext2D): void;
        HitTest(point: TcHmi.Common.BaseTypes.Point): boolean;
        CalculateTransformMatrixAt(position: number, includeGlobalTransformation?: boolean): TcHmi.Common.BaseTypes.M3;
        private DrawDebugVisuals;
    }
}
declare module TcHmi.XTS.Controls {
    class XInfoBarVisual extends TcHmi.Common.Scenegraph.RenderableBase {
        private markerGroupVisual;
        private textGroupVisual;
        private infoBarModel;
        private segmentPoints;
        private renderer;
        constructor(infoBarModel: XInfoBarModel, markerRenderer: TcHmi.Common.Scenegraph.IRenderableCollection, zIndex?: number);
        get InfoBarModel(): XInfoBarModel;
        get MarkerGroupVisual(): TcHmi.Common.Scenegraph.VisualGroup<XInfoBarMarkerVisual>;
        get TextGroupVisual(): TcHmi.Common.Scenegraph.VisualGroup<TcHmi.Common.Scenegraph.TextNode>;
        get Renderer(): TcHmi.Common.Scenegraph.IRenderableCollection;
        InitializeRender(): void;
        Render(ctx: CanvasRenderingContext2D): void;
        private RenderSegments;
        GetStartPoint(): TcHmi.Common.BaseTypes.Point;
        GetBounds(): Common.BaseTypes.Rect;
    }
}
declare module TcHmi.XTS.Controls {
    class XtsPartVisual extends TcHmi.Common.Scenegraph.TransformableBase {
        private trackLength;
        RotationServer: number;
        OffsetServer: Common.BaseTypes.Point;
        PartSideServer: TcHmi.XTS.BaseTypes.ModuleSide;
        moduleGroup: TcHmi.Common.Scenegraph.VisualGroup<XtsModuleVisual>;
        infoBarGroup: TcHmi.Common.Scenegraph.VisualGroup<XInfoBarVisual>;
        moverGroup: TcHmi.Common.Scenegraph.VisualGroup<XtsMoverVisual>;
        readonly PartRenderer: TcHmi.Common.Scenegraph.IRenderableCollection;
        partSide: TcHmi.XTS.BaseTypes.ModuleSide;
        private globalNumber;
        private partIndex;
        private processingUnitIndex;
        constructor(globalNumber: number, xpuIndex: number, partIndex: number, partRenderer: TcHmi.Common.Scenegraph.IRenderableCollection);
        get IndexInXpu(): number;
        get ProcessingUnitIndex(): number;
        get GlobalNumber(): number;
        get TrackLength(): number;
        static CreateFromExisting(partVisual: XtsPartVisual): XtsPartVisual;
        AddExistingMover(moverVisual: XtsMoverVisual, position: number): void;
        RemoveMover(xtsMoverVisual: XtsMoverVisual): void;
        AddModule(metaData: ModuleMetaData, gap: number, loadedCallback?: () => void): void;
        TransformMoverToPosition(moverVisual: XtsMoverVisual, position: number): void;
        GetModuleVisualContaining(position: number): XtsModuleVisual | null;
        LoadPart(xtsPart: TcHmi.XTS.Server.ServerTypes.PartModel, moduleSide: TcHmi.XTS.BaseTypes.ModuleSide, partLoadedCallback?: () => void): void;
        private CheckModuleSupport;
        LoadPartFromExisting(partVisual: XtsPartVisual, partSide: TcHmi.XTS.BaseTypes.ModuleSide, partLoadedCallback?: () => void): void;
        ClearTools(): void;
        HitTest(point: TcHmi.Common.BaseTypes.Point): XtsMoverVisual | XtsModuleVisual | null;
        CreateInfoBar(init: Partial<XInfoBarModel>, zIndex: number): XInfoBarModel;
        CalculateDisplacementPoints(partStart: number, partEnd: number, displacement: number): TcHmi.Common.BaseTypes.Point[];
    }
}
declare module TcHmi {
    module XTS {
        module Controls {
            class XtsView extends TcHmi.Controls.System.TcHmiControl {
                /**
                 * @description Constructor of the control
                 * @param {JQuery} element Element from HTML (internal, do not use)
                 * @param {JQuery} pcElement precompiled Element (internal, do not use)
                 * @param {TcHmi.Controls.ControlAttributeList} attrs Attributes defined in HTML in a special format (internal, do not use)
                 * @returns {void}
                 */
                private serverConnection;
                private systemRenderer;
                private systemVisual;
                private interactionHandler;
                private selectionManager;
                private resizeEventDestroyFunction;
                private refreshRate;
                constructor(element: JQuery, pcElement: JQuery, attrs: TcHmi.Controls.ControlAttributeList);
                /**
                  * If raised, the control object exists in control cache and constructor of each inheritation level was called.
                  * Call attribute processor functions here to initialize default values!
                  */
                __previnit(): void;
                /**
                 * @description Is called during control initialize phase after attribute setter have been called based on it's default or initial html dom values.
                 * @returns {void}
                 */
                __init(): void;
                /**
                * @description Is called by tachcontrol() after the control instance gets part of the current DOM.
                * Is only allowed to be called from the framework itself!
                */
                __attach(): void;
                /**
              * @description Is called by tachcontrol() after the control instance is no longer part of the current DOM.
              * Is only allowed to be called from the framework itself!
              */
                __detach(): void;
                /**
               * @description Destroy the current control instance.
               * Will be called automatically if system destroys control!
               */
                destroy(): void;
                private InitControl;
                private InitMoverSubscription;
                private AttachControl;
                private DeinitControl;
                private AddPartTransformationSubscription;
                private AddDriveStateSubscription;
                CreateCanvas(): void;
                private Resized;
                GetTargetName(): string | undefined;
                SetTargetName(targetName: string): void;
                GetRefreshRate(): number;
                SetRefreshRate(refreshRate: number): void;
                GetInfoImages(): ClientTypes.XtsInfoImage[];
                SetInfoImages(images: ClientTypes.XtsInfoImage[]): void;
                GetLockPan(): boolean;
                SetLockPan(lock: boolean): void;
                GetLockZoom(): boolean;
                SetLockZoom(lock: boolean): void;
                SetToolArray(toolArray: any): void;
                GetToolArray(): ClientTypes.XtsTool[];
                SetPartTransformations(partTransformations: any): void;
                GetPartTransformations(): ClientTypes.PartTransformation[];
                SetLayout(layout: ClientTypes.XtsLayout): void;
                GetLayout(): string;
                GetPadding(): any;
                SetPadding(padding: any): void;
                SetModuleSelection(selectedModulesNew: ClientTypes.XtsModule[]): void;
                GetModuleSelection(): ClientTypes.XtsModule[];
                SetMoverSelection(selectedMoverNew: ClientTypes.XtsMover[]): void;
                GetMoverSelection(): ClientTypes.XtsMover[];
                SetModuleSelectionColor(color: TcHmi.SolidColor): void;
                GetModuleSelectionColor(): TcHmi.SolidColor;
                SetMoverSelectionColor(color: TcHmi.SolidColor): void;
                GetMoverSelectionColor(): TcHmi.SolidColor;
                SetSelectionMode(newSelectionMode: ClientTypes.SelectionMode): void;
                GetSelectionMode(): ClientTypes.SelectionMode;
                SetStationOptions(stationOptions: any): void;
                GetStationOptions(): ClientTypes.StationOptions;
                SetDisplayStations(displayStations: boolean): void;
                GetDisplayStations(): boolean;
                SetStationMarkerOptions(stationMarkerOptions: any): void;
                GetMarkerOptions(): ClientTypes.MarkerOptions;
                SetDisplayDimensions(displayDimensions: boolean): void;
                GetDisplayDimensions(): boolean;
                SetDimensionOptions(dimensionOptions: any): void;
                GetDimensionOptions(): ClientTypes.DimensionOptions;
                SetInfoBars(infoBars: any): void;
                GetInfoBars(): ClientTypes.XtsInfoBar[];
                SetInfoBarOptions(infoBarOptions: any): void;
                GetInfoBarOptions(): ClientTypes.InfoBarOptions;
                GetInvertDimensions(): boolean;
                SetInvertDimensions(invertDimensions: boolean): void;
                GetTransformation(): number[][];
                SetTransformation(values: number[][]): void;
                SetViewRotation(rotation: number): void;
                GetViewRotation(): number;
                SetMoverType(moverType: ClientTypes.MoverType): void;
                GetMoverType(): ClientTypes.MoverType;
                SetCustomMoverLayout(moverLayout: ClientTypes.CustomMoverLayout): void;
                GetCustomMoverLayout(): ClientTypes.CustomMoverLayout;
                SetShowDriveErrors(showError: boolean): void;
                GetShowDriveErrors(): boolean;
                SetShowDriveWarnings(showWarning: boolean): void;
                GetShowDriveWarnings(): boolean;
                private ObjectResolverHandler;
                ZoomToFit(): void;
            }
        }
    }
}
declare module TcHmi.XTS.Controls {
    class XInfoBarMarkerVisual extends TcHmi.Common.Scenegraph.RenderableBase {
        private infoBarMarkerModel;
        private textGroupVisual;
        constructor(infoBarMarkerModel: XInfoBarMarkerModel, textRenderer: TcHmi.Common.Scenegraph.IRenderableCollection, zIndex?: number);
        get MarkerModel(): XInfoBarMarkerModel;
        get TextGroupVisual(): TcHmi.Common.Scenegraph.VisualGroup<TcHmi.Common.Scenegraph.TextNode>;
        Render(ctx: CanvasRenderingContext2D): void;
        private RenderMarker;
    }
}
declare module TcHmi.XTS.Controls {
    class XInfoBarModel {
        private displacement;
        private partEnd;
        private partStart;
        Thickness: number;
        Color: string;
        Marker: XInfoBarMarkerModel[];
        Id: number;
        Visual: XInfoBarVisual;
        PartVisual: XtsPartVisual;
        constructor(init?: Partial<XInfoBarModel>);
        get Displacement(): number;
        set Displacement(displacement: number);
        get PartEnd(): number;
        set PartEnd(partEnd: number);
        get PartStart(): number;
        set PartStart(partStart: number);
        CreateMarker(init: Partial<XInfoBarMarkerModel>, zIndex: number): XInfoBarMarkerModel;
        AddTextNode(textConfig: TcHmi.Common.BaseTypes.TextConfiguration, placement: TcHmi.HorizontalAlignment, displacement: number): void;
        contains(station: XInfoBarModel): boolean;
        DeleteFromPart(): void;
        private UpdateVisual;
        private UpdateMarkerTransformationFor;
        private UpdateTextTransformationFor;
    }
}
declare module TcHmi.XTS.Controls {
    class XInfoBarMarkerModel {
        PartPosition: number;
        MarkerType: ClientTypes.MarkerType;
        Color: string;
        Size: number;
        Thickness: number;
        Visual: XInfoBarMarkerVisual;
        InfoBar: XInfoBarModel;
        constructor(init?: Partial<XInfoBarMarkerModel>);
        AddTextNode(textConfig: TcHmi.Common.BaseTypes.TextConfiguration, displacement: number, zIndex: number): void;
    }
}
declare module TcHmi.XTS.Controls {
    class InfoBarLayouter {
        private part;
        private levels;
        constructor(part: XtsPartVisual);
        Layout(displacementToFirst: number, spaceBetween: number): void;
        private CanAddToLevel;
    }
}
declare module TcHmi.XTS.Controls {
    class StationTextModel {
        Displacement: number;
        TextConfig: Common.BaseTypes.TextConfiguration;
        Placement: TcHmi.HorizontalAlignment;
        Visual: Common.Scenegraph.TextNode;
        constructor(init?: Partial<StationTextModel>);
    }
}
declare module TcHmi.XTS.Controls {
    class GlobalMoverList {
        Locations: TcHmi.XTS.Server.ServerTypes.MoverPosition[][];
        private moverList;
        get Length(): number;
        get Movers(): Iterable<Iterable<XtsMoverVisual>>;
        get MoverList(): XtsMoverVisual[][];
        RegisterXpu(iXpu: number, moverList: XtsMoverVisual[]): void;
        GetMoverByIndex(iXpu: number, iMover: number): XtsMoverVisual | null;
        GetMoversById(iXpu: number, id: string): XtsMoverVisual[];
        Clear(): void;
        ClearFor(xpuIndex: number): void;
        Replace(iXpu: number, iMover: number, newMoverVisual: XtsMoverVisual): void;
        IndexOf(moverVisual: XtsMoverVisual): ClientTypes.XtsMover | null;
    }
}
declare module TcHmi.XTS.Controls {
    class XSystemVisual extends Common.Scenegraph.TransformableBase {
        private transformationChanged;
        private xtsPartGroupVisual;
        private infoImagesGroupVisual;
        private moverList;
        private xtsPartsVisual;
        private systemRenderer;
        private xtsPartsVisualByGlobalId;
        private partsVisualByProcessingUnitIndex;
        private xtsStationModels;
        private dimensionModels;
        private infoBarModels;
        private rotation;
        private lastMoverPositions;
        private customMoverMetaDataFront;
        private customMoverMetaDataBack;
        private customMoverLayout;
        private moverType;
        private toolArray;
        private partTransformationsClient;
        private partTransformationsServer;
        private layout;
        private infoImages;
        private stationOptions;
        private stationMarkerOptions;
        private displayStations;
        private stations;
        private displayDimensions;
        private invertDimensions;
        private dimensionOptions;
        private infoBars;
        private infoBarOptions;
        private xtsModel;
        private moduleDriveStates;
        private isShowDriveErrorEnabled;
        private isShowDriveWarningEnabled;
        private basePath;
        constructor(systemRenderer: TcHmi.Common.Scenegraph.XSystemRenderer, basePath: string);
        get BasePath(): string;
        get CustomMoverLayout(): ClientTypes.CustomMoverLayout;
        set CustomMoverLayout(moverLayout: ClientTypes.CustomMoverLayout);
        get MoverType(): ClientTypes.MoverType;
        set MoverType(moverType: ClientTypes.MoverType);
        get DimensionOptions(): ClientTypes.DimensionOptions;
        set DimensionOptions(dimensionOptions: ClientTypes.DimensionOptions);
        get DisplayDimensions(): boolean;
        set DisplayDimensions(displayDimensions: boolean);
        get IsShowDriveErrorEnabled(): boolean;
        set IsShowDriveErrorEnabled(isShowDriveErrorEnabled: boolean);
        get IsShowDriveWarningEnabled(): boolean;
        set IsShowDriveWarningEnabled(isShowWarningErrorEnabled: boolean);
        get ModuleDriveStates(): number[][];
        set ModuleDriveStates(driveStates: number[][]);
        get MoverList(): GlobalMoverList;
        get Rotation(): number;
        set Rotation(rotation: number);
        set TransformationChanged(changed: (m3: TcHmi.Common.BaseTypes.M3) => void | null);
        get XtsPartGroupVisual(): TcHmi.Common.Scenegraph.TransformableBase;
        get XtsPartsVisual(): XtsPartVisual[];
        set ToolArray(tools: ClientTypes.XtsTool[]);
        get ToolArray(): ClientTypes.XtsTool[];
        get PartTransformationsClient(): ClientTypes.PartTransformation[];
        set PartTransformationsClient(partTransformations: ClientTypes.PartTransformation[]);
        get PartTransformationsServer(): TcHmi.XTS.Server.ServerTypes.PartTransformation[][];
        set PartTransformationsServer(partTransformations: TcHmi.XTS.Server.ServerTypes.PartTransformation[][]);
        set Layout(layout: ClientTypes.XtsLayout);
        get Layout(): ClientTypes.XtsLayout;
        set InfoImages(infoImages: ClientTypes.XtsInfoImage[]);
        get InfoImages(): ClientTypes.XtsInfoImage[];
        set StationOptions(stationOptions: ClientTypes.StationOptions);
        get StationOptions(): ClientTypes.StationOptions;
        set StationMarkerOptions(stationMarkerOptions: ClientTypes.MarkerOptions);
        get StationMarkerOptions(): ClientTypes.MarkerOptions;
        get DisplayStations(): boolean;
        set DisplayStations(displayStations: boolean);
        get InvertDimensions(): boolean;
        set InvertDimensions(invertDimensions: boolean);
        get Stations(): TcHmi.XTS.Server.ServerTypes.StationModel[];
        set Stations(stations: TcHmi.XTS.Server.ServerTypes.StationModel[]);
        get InfoBars(): ClientTypes.XtsInfoBar[];
        set InfoBars(infoBars: ClientTypes.XtsInfoBar[]);
        set InfoBarOptions(infoBarOptions: ClientTypes.InfoBarOptions);
        get InfoBarOptions(): ClientTypes.InfoBarOptions;
        GetPartsForXpuIndex(iXpu: number): XtsPartVisual[];
        AddPartVisual(partVisual: XtsPartVisual): void;
        CheckTransformationForReload(): boolean;
        CreateMoverVisuals(moverModels: TcHmi.XTS.Server.ServerTypes.MoverModel[], xpuIndex: number, moverType: TcHmi.XTS.BaseTypes.MoverType, loadedCallback?: () => void): XtsMoverVisual[];
        CreateVisuals(model: TcHmi.XTS.Server.ServerTypes.XtsModel, laodedCallback?: () => void): void;
        Delete(): void;
        HitTest(point: TcHmi.Common.BaseTypes.Point): XtsMoverVisual | XtsModuleVisual | null;
        ReloadDimensions(): void;
        ReloadInfoBars(): void;
        ReloadInfoImagesAsync(): Promise<void>;
        ReloadInfoImages(): void;
        ReloadMoverTools(): void;
        ReloadPartTransformations(): void;
        ReloadStations(): void;
        UpdateInfoBars(): void;
        UpdateMoverPositions(moverLocations: TcHmi.XTS.Server.ServerTypes.MoverPosition[][]): void;
        TransformNode(m3: Common.BaseTypes.M3): void;
        private DeleteDimensions;
        private DeleteInfoBars;
        private DeleteMoverVisualFor;
        private DeleteMoverVisual;
        private DeletePartsVisual;
        private DeleteStations;
        private DeleteToolsVisual;
        private GetPartSideOf;
        private ReloadMoverToolsFor;
        private CreateNewMoverVisual;
        private UpdateShowModuleDriveWarningError;
    }
}
declare module TcHmi.XTS.Controls {
    class SelectionManager {
        private selectionMode;
        private moduleSelectionColor;
        private moverSelectionColor;
        private moverSelection;
        private moduleSelection;
        private systemVisual;
        private systemRenderer;
        private moverSelectionChanged;
        private moduleSelectionChanged;
        constructor(systemVisual: XSystemVisual, systemRenderer: TcHmi.Common.Scenegraph.XSystemRenderer, moverSelectionChanged: (selection: ClientTypes.XtsMover[]) => void, moduleSelectionChanged: (selection: ClientTypes.XtsModule[]) => void);
        get SelectionMode(): ClientTypes.SelectionMode;
        set SelectionMode(selectionMode: ClientTypes.SelectionMode);
        get ModuleSelection(): ClientTypes.XtsModule[];
        set ModuleSelection(newSelection: ClientTypes.XtsModule[]);
        get ModuleSelectionColor(): TcHmi.SolidColor;
        set ModuleSelectionColor(moduleSelectionColor: TcHmi.SolidColor);
        get MoverSelection(): ClientTypes.XtsMover[];
        set MoverSelection(newSelection: ClientTypes.XtsMover[]);
        get MoverSelectionColor(): TcHmi.SolidColor;
        set MoverSelectionColor(moverSelectionColor: TcHmi.SolidColor);
        ReloadMoverSelection(): void;
        ReloadModuleSelection(): void;
        Click(point: TcHmi.Common.BaseTypes.Point): null | undefined;
    }
}
