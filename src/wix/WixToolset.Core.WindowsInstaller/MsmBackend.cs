// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

namespace WixToolset.Core.WindowsInstaller
{
    using WixToolset.Core.WindowsInstaller.Bind;
    using WixToolset.Core.WindowsInstaller.Decompile;
    using WixToolset.Core.WindowsInstaller.Unbind;
    using WixToolset.Data;
    using WixToolset.Extensibility;
    using WixToolset.Extensibility.Data;
    using WixToolset.Extensibility.Services;

    internal class MsmBackend : IBackend
    {
        public IBindResult Bind(IBindContext context)
        {
            var extensionManager = context.ServiceProvider.GetService<IExtensionManager>();

            var backendExtensions = extensionManager.GetServices<IWindowsInstallerBackendBinderExtension>();

            foreach (var extension in backendExtensions)
            {
                extension.PreBackendBind(context);
            }

            IBindResult result = null;
            try
            {
                var command = new BindDatabaseCommand(context, backendExtensions);
                result = command.Execute();

                foreach (var extension in backendExtensions)
                {
                    extension.PostBackendBind(result);
                }

                return result;
            }
            catch
            {
                result?.Dispose();
                throw;
            }
        }

        public IDecompileResult Decompile(IDecompileContext context)
        {
            var extensionManager = context.ServiceProvider.GetService<IExtensionManager>();

            var backendExtensions = extensionManager.GetServices<IWindowsInstallerBackendDecompilerExtension>();

            foreach (var extension in backendExtensions)
            {
                extension.PreBackendDecompile(context);
            }

            var command = new DecompileMsiOrMsmCommand(context, backendExtensions);
            var result = command.Execute();

            foreach (var extension in backendExtensions)
            {
                extension.PostBackendDecompile(result);
            }

            return result;
        }

        public Intermediate Unbind(IUnbindContext context)
        {
            var command = new UnbindMsiOrMsmCommand(context);
            return command.Execute();
        }
    }
}
