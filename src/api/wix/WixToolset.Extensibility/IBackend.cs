// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

namespace WixToolset.Extensibility
{
    using WixToolset.Data;
    using WixToolset.Extensibility.Data;

#pragma warning disable 1591 // TODO: add documentation
    public interface IBackend
    {
        IBindResult Bind(IBindContext context);

        IDecompileResult Decompile(IDecompileContext context);

        Intermediate Unbind(IUnbindContext context);
    }
}
